INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include


#>>>--------------------------------------------------------------------------------------------------------------------------------------------
# Boost

#boost_atomic
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/boost/release/ -lboost_atomic
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/boost/debug/ -lboost_atomic
else:unix: LIBS += -L$$PWD/../lib/boost/ -lboost_atomic

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/libboost_atomic.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/libboost_atomic.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/boost_atomic.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/boost_atomic.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/boost/libboost_atomic.a

#boost_chrono
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/boost/release/ -lboost_chrono
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/boost/debug/ -lboost_chrono
else:unix: LIBS += -L$$PWD/../lib/boost/ -lboost_chrono

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/libboost_chrono.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/libboost_chrono.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/boost_chrono.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/boost_chrono.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/boost/libboost_chrono.a

#boost_container
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/boost/release/ -lboost_container
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/boost/debug/ -lboost_container
else:unix: LIBS += -L$$PWD/../lib/boost/ -lboost_container

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/libboost_container.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/libboost_container.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/boost_container.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/boost_container.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/boost/libboost_container.a

#boost_context
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/boost/release/ -lboost_context
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/boost/debug/ -lboost_context
else:unix: LIBS += -L$$PWD/../lib/boost/ -lboost_context

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/libboost_context.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/libboost_context.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/boost_context.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/boost_context.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/boost/libboost_context.a

#boost_coroutine
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/boost/release/ -lboost_coroutine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/boost/debug/ -lboost_coroutine
else:unix: LIBS += -L$$PWD/../lib/boost/ -lboost_coroutine

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/libboost_coroutine.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/libboost_coroutine.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/boost_coroutine.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/boost_coroutine.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/boost/libboost_coroutine.a

#boost_date_time
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/boost/release/ -lboost_date_time
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/boost/debug/ -lboost_date_time
else:unix: LIBS += -L$$PWD/../lib/boost/ -lboost_date_time

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/libboost_date_time.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/libboost_date_time.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/boost_date_time.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/boost_date_time.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/boost/libboost_date_time.a

#boost_exception
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/boost/release/ -lboost_exception
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/boost/debug/ -lboost_exception
else:unix: LIBS += -L$$PWD/../lib/boost/ -lboost_exception

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/libboost_exception.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/libboost_exception.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/boost_exception.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/boost_exception.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/boost/libboost_exception.a

#boost_filesystem
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/boost/release/ -lboost_filesystem
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/boost/debug/ -lboost_filesystem
else:unix: LIBS += -L$$PWD/../lib/boost/ -lboost_filesystem

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/libboost_filesystem.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/libboost_filesystem.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/boost_filesystem.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/boost_filesystem.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/boost/libboost_filesystem.a

#  boost_iostreams
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/boost/release/ -lboost_iostreams
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/boost/debug/ -lboost_iostreams
else:unix: LIBS += -L$$PWD/../lib/boost/ -lboost_iostreams

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/libboost_iostreams.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/libboost_iostreams.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/boost_iostreams.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/boost_iostreams.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/boost/libboost_iostreams.a

#  boost_locale
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/boost/release/ -lboost_locale
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/boost/debug/ -lboost_locale
else:unix: LIBS += -L$$PWD/../lib/boost/ -lboost_locale

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/libboost_locale.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/libboost_locale.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/boost_locale.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/boost_locale.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/boost/libboost_locale.a

#boost_program_options
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/boost/release/ -lboost_program_options
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/boost/debug/ -lboost_program_options
else:unix: LIBS += -L$$PWD/../lib/boost/ -lboost_program_options

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/libboost_program_options.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/libboost_program_options.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/boost_program_options.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/boost_program_options.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/boost/libboost_program_options.a

#  boost_serialization
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/boost/release/ -lboost_serialization
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/boost/debug/ -lboost_serialization
else:unix: LIBS += -L$$PWD/../lib/boost/ -lboost_serialization

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/libboost_serialization.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/libboost_serialization.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/boost_serialization.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/boost_serialization.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/boost/libboost_serialization.a

#boost_signals
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/boost/release/ -lboost_signals
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/boost/debug/ -lboost_signals
else:unix: LIBS += -L$$PWD/../lib/boost/ -lboost_signals

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/libboost_signals.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/libboost_signals.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/boost_signals.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/boost_signals.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/boost/libboost_signals.a

#boost_system
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/boost/release/ -lboost_system
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/boost/debug/ -lboost_system
else:unix: LIBS += -L$$PWD/../lib/boost/ -lboost_system

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/libboost_system.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/libboost_system.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/boost_system.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/boost_system.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/boost/libboost_system.a

#boost_thread
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/boost/release/ -lboost_thread
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/boost/debug/ -lboost_thread
else:unix: LIBS += -L$$PWD/../lib/boost/ -lboost_thread

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/libboost_thread.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/libboost_thread.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/boost_thread.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/boost_thread.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/boost/libboost_thread.a

#boost_regex
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/boost/release/ -lboost_regex
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/boost/debug/ -lboost_regex
else:unix: LIBS += -L$$PWD/../lib/boost/ -lboost_regex

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/libboost_regex.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/libboost_regex.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/boost_regex.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/boost_regex.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/boost/libboost_regex.a

#boost_type_erasure
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/boost/release/ -lboost_type_erasure
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/boost/debug/ -lboost_type_erasure
else:unix: LIBS += -L$$PWD/../lib/boost/ -lboost_type_erasure

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/libboost_type_erasure.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/libboost_type_erasure.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/release/boost_type_erasure.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/boost/debug/boost_type_erasure.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/boost/libboost_type_erasure.a

#<<<--------------------------------------------------------------------------------------------------------------------------------------------

#>>>--------------------------------------------------------------------------------------------------------------------------------------------
# Sqlite
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/release/ -lsqlite3
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/debug/ -lsqlite3
else:unix:!macx: LIBS += -L$$PWD/../lib/ -lsqlite3

INCLUDEPATH += $$PWD/../include/sqlite
DEPENDPATH += $$PWD/../include/sqlite

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/release/libsqlite3.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/debug/libsqlite3.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/release/sqlite3.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/debug/sqlite3.lib
else:unix:!macx: PRE_TARGETDEPS += $$PWD/../lib/libsqlite3.a
#<<<--------------------------------------------------------------------------------------------------------------------------------------------

#>>>--------------------------------------------------------------------------------------------------------------------------------------------
# Parquet

#parquet
INCLUDEPATH += $$PWD/../include/parquet
DEPENDPATH += $$PWD/../include/parquet

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/parquet/release/ -lparquet
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/parquet/debug/ -lparquet
else:unix: LIBS += -L$$PWD/../lib/ -lparquet

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/release/ libparquet.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/debug/ libparquet.a
else:unix: PRE_TARGETDEPS += $$PWD/../lib/parquet/libparquet.a

#snappy
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/parquet/release/ -lsnappy
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/parquet/debug/ -lsnappy
else:unix: LIBS += -L$$PWD/../lib/parquet/ -lsnappy

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/release/libsnappy.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/debug/libsnappy.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/release/snappy.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/debug/snappy.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/parquet/libsnappy.a

#libz
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/parquet/release/ -lz
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/parquet/debug/ -lz
else:unix: LIBS += -L$$PWD/../lib/parquet/ -lz

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/release/libz.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/debug/libz.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/release/z.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/debug/z.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/parquet/libz.a

#thriftd
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/parquet/release/ -lthriftd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/parquet/debug/ -lthriftd
else:unix: LIBS += -L$$PWD/../lib/parquet/ -lthriftd

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/release/libthriftd.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/debug/libthriftd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/release/thriftd.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/debug/thriftd.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/parquet/libthriftd.a

#arrow_io
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/parquet/release/ -larrow_io
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/parquet/debug/ -larrow_io
else:unix: LIBS += -L$$PWD/../lib/parquet/ -larrow_io

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/release/libarrow_io.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/debug/libarrow_io.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/release/arrow_io.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/debug/arrow_io.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/parquet/libarrow_io.a

#arrow
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/parquet/release/ -larrow
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/parquet/debug/ -larrow
else:unix: LIBS += -L$$PWD/../lib/parquet/ -larrow

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/release/libarrow.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/debug/libarrow.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/release/arrow.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/debug/arrow.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/parquet/libarrow.a

#brotlicommon
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/parquet/release/ -lbrotlicommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/parquet/debug/ -lbrotlicommon
else:unix: LIBS += -L$$PWD/../lib/parquet/ -lbrotlicommon

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/release/libbrotlicommon.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/debug/libbrotlicommon.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/release/brotlicommon.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/debug/brotlicommon.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/parquet/libbrotlicommon.a

#brotlidec
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/parquet/release/ -lbrotlidec
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/parquet/debug/ -lbrotlidec
else:unix: LIBS += -L$$PWD/../lib/parquet/ -lbrotlidec

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/release/libbrotlidec.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/debug/libbrotlidec.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/release/brotlidec.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/debug/brotlidec.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/parquet/libbrotlidec.a

#brotlienc
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/parquet/release/ -lbrotlienc
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/parquet/debug/ -lbrotlienc
else:unix: LIBS += -L$$PWD/../lib/parquet/ -lbrotlienc

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/release/libbrotlienc.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/debug/libbrotlienc.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/release/brotlienc.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/parquet/debug/brotlienc.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/parquet/libbrotlienc.a

#<<<--------------------------------------------------------------------------------------------------------------------------------------------

#>>>--------------------------------------------------------------------------------------------------------------------------------------------
# protobuf

INCLUDEPATH += $$PWD/../include/protobuf
DEPENDPATH += $$PWD/../include/protobuf

#protobuf
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/protobuf/release/ -lprotobuf
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/protobuf/debug/ -lprotobuf
else:unix: LIBS += -L$$PWD/../lib/protobuf/ -lprotobuf

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/protobuf/release/libprotobuf.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/protobuf/debug/libprotobuf.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lib/protobuf/release/protobuf.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lib/protobuf/debug/protobuf.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lib/protobuf/libprotobuf.a

#<<<-------------------------------------------------------------------------------------------------------------------------------------------


#>>>--------------------------------------------------------------------------------------------------------------------------------------------
#some basic lib

#TBC window下的待添加

unix:!macx: LIBS +=  -L/usr/lib/x86_64-linux-gnu\
-lQt5Core\
-lQt5Gui\
-lQt5Widgets \
-lQt5Test \
-lQt5Concurrent\
-lQt5OpenGL\
-ldl

#<<<--------------------------------------------------------------------------------------------------------------------------------------------
