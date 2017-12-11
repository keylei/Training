// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#ifndef ARROW_UTIL_VISIBILITY_H
#define ARROW_UTIL_VISIBILITY_H

#if defined(_WIN32) || defined(__CYGWIN__)
#if defined(_MSC_VER)
#pragma warning(disable : 4251)
#else
#pragma GCC diagnostic ignored "-Wattributes"
#endif
#define ARROW_EXPORT __declspec(dllexport)
#define ARROW_NO_EXPORT
#else  // Not Windows
#ifndef ARROW_EXPORT
#define ARROW_EXPORT __attribute__((visibility("default")))
#endif
#ifndef ARROW_NO_EXPORT
#define ARROW_NO_EXPORT __attribute__((visibility("hidden")))
#endif
#endif  // Non-Windows

#endif  // ARROW_UTIL_VISIBILITY_H