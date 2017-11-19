#ifndef SQLITEDB_HPP_INL
#define SQLITEDB_HPP_INL

template< typename R,typename... Args>
R SSDK::DB::SqliteDB::executeScalar(const std::string& sqlStr,Args&&... args)
{
    if(!this->prepare(sqlStr))
    {
        return getErrorVale<R>();
    }

    //绑定sql脚本中参数
    if(SQLITE_OK != bindParams(this->m_pstatement,1,std::forward<Args>(args)...))
    {
        return getErrorVale<R>();
    }

    this->m_latestResultCode = sqlite3_step(this->m_pstatement);

    if(this->m_latestResultCode != SQLITE_ROW)
    {
        return getErrorVale<R>();
    }

    sqliteValue val = getColumnValue(this->m_pstatement,0);
    auto result = boost::get<R>(val);
    sqlite3_reset(this->m_pstatement);
    return result;
}

//执行带参数的Sql语句，如插入一条记录
template<typename... Args>
bool SSDK::DB::SqliteDB::execute(const std::string& sqlStr,Args &&...args)
{
    if(!this->prepare(sqlStr))
    {
        return false;
    }

    return executeArgs(std::forward<Args>(args)...);
}

template<typename Tuple>
bool SSDK::DB::SqliteDB::excecuteTuple(const std::string& sqlStr, Tuple&& t)
{
    if(!prepare(sqlStr))
    {
        return false;
    }

    return excecuteTuple(
                typename makeIndexes<std::tuple_size<Tuple>::value>::type(),
                std::forward<Tuple>(t));
}

template<int... indexes,typename Tuple>
bool SSDK::DB::SqliteDB::excecuteTuple(Sung::SSDK::DB::SqliteDB::indexTuple<indexes...>&& in,Tuple&& t)
{
   if(SQLITE_OK != bindParams(this->m_pstatement,1,std::get<indexes>(std::forward<Tuple>(t))...))
   {
       return false;
   }

   this->m_latestResultCode = sqlite3_step(this->m_pstatement);
   sqlite3_reset(this->m_pstatement);
   return this->m_latestResultCode == SQLITE_DONE;
}

//返回无效值
template< typename T>
typename std::enable_if<std::is_arithmetic<T>::value,T>::type
SSDK::DB::SqliteDB::getErrorVale()
{
    return T(-9999);
}

template< typename T>
typename std::enable_if<!std::is_arithmetic<T>::value && !std::is_same<T,Sung::SSDK::DB::SqliteDB::Blob>::value,T>::type
SSDK::DB::SqliteDB::getErrorVale()
{
    return "";
}

template< typename T>
typename std::enable_if<std::is_same<T,Sung::SSDK::DB::SqliteDB::Blob>::value,T>::type
SSDK::DB::SqliteDB::getErrorVale()
{
    return {nullptr,0};
}


#endif // SQLITEDB_HPP_INL
