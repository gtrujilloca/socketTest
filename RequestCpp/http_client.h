//  /**
//    * ==++==
//    *
//    * Copyright (c) Microsoft Corporation. All rights reserved.
//    * Licensed under the Apache License, Version 2.0 (the "License");
//    * you may not use this file except in compliance with the License.
//    * You may obtain a copy of the License at
//    * http://www.apache.org/licenses/LICENSE-2.0
//    *
//    * Unless required by applicable law or agreed to in writing, software
//    * distributed under the License is distributed on an "AS IS" BASIS,
//    * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    * See the License for the specific language governing permissions and
//    * limitations under the License.
//    *
//    * ==--==
//    * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
//    *
//    * HTTP Library: Client-side APIs.
//    *
//    * For the latest on this and related APIs, please see http://casablanca.codeplex.com.
//    *
//    * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//    ****/
//    #pragma once
   
//    #ifndef _CASA_HTTP_CLIENT_H
//    #define _CASA_HTTP_CLIENT_H
   
//    #if defined (__cplusplus_winrt)
//    #if !defined(__WRL_NO_DEFAULT_LIB__)
//    #define __WRL_NO_DEFAULT_LIB__
//    #endif
//    #include <wrl.h>
//    #include <msxml6.h>
//    namespace web { namespace http{namespace client{
//    typedef IXMLHTTPRequest2* native_handle;}}}
//    #else
//    namespace web { namespace http{namespace client{
//    typedef void* native_handle;}}}
//    #endif // __cplusplus_winrt
   
//    #include <memory>
//    #include <limits>
//    #if !defined(_WIN32) && !defined(__cplusplus_winrt)
//    #if defined(__clang__)
//    #pragma clang diagnostic push
//    #pragma clang diagnostic ignored "-Wconversion"
//    #endif
//    #include "boost/asio/ssl.hpp"
//    #if defined(__clang__)
//    #pragma clang diagnostic pop
//    #endif
//    #endif
   
//    #include "pplx/pplxtasks.h"
//    #include "cpprest/http_msg.h"
//    #include "cpprest/json.h"
//    #include "cpprest/uri.h"
//    #include "cpprest/details/web_utilities.h"
//    #include "cpprest/details/basic_types.h"
//    #include "cpprest/asyncrt_utils.h"
   
//    #if !defined(CPPREST_TARGET_XP)
//    #include "cpprest/oauth1.h"
//    #endif
   
//    #include "cpprest/oauth2.h"
   
//    namespace web
//    {
//    namespace http
//    {
//    namespace client
//    {
   
//    // credentials and web_proxy class has been moved from web::http::client namespace to web namespace.
//    // The below using declarations ensure we don't break existing code.
//    // Please use the web::credentials and web::web_proxy class going forward.
//    using web::credentials;
//    using web::web_proxy;
   
//    class http_client_config
//    {
//    public:
//        http_client_config() :
//            m_guarantee_order(false),
//            m_timeout(std::chrono::seconds(30)),
//            m_chunksize(0)
//    #if !defined(__cplusplus_winrt)
//            , m_validate_certificates(true)
//    #endif
//            , m_set_user_nativehandle_options([](native_handle)->void{})
//    #if !defined(_WIN32) && !defined(__cplusplus_winrt)
//            , m_ssl_context_callback([](boost::asio::ssl::context&)->void{})
//    #endif
//    #if defined(_WIN32) && !defined(__cplusplus_winrt)
//            , m_buffer_request(false)
//    #endif
//        {
//        }
   
//    #if !defined(CPPREST_TARGET_XP)
//        const std::shared_ptr<oauth1::experimental::oauth1_config> oauth1() const
//        {
//            return m_oauth1;
//        }
   
//        void set_oauth1(oauth1::experimental::oauth1_config config)
//        {
//            m_oauth1 = std::make_shared<oauth1::experimental::oauth1_config>(std::move(config));
//        }
//    #endif
   
//        const std::shared_ptr<oauth2::experimental::oauth2_config> oauth2() const
//        {
//            return m_oauth2;
//        }
   
//        void set_oauth2(oauth2::experimental::oauth2_config config)
//        {
//            m_oauth2 = std::make_shared<oauth2::experimental::oauth2_config>(std::move(config));
//        }
   
//        const web_proxy& proxy() const
//        {
//            return m_proxy;
//        }
   
//        void set_proxy(web_proxy proxy)
//        {
//            m_proxy = std::move(proxy);
//        }
   
//        const http::client::credentials& credentials() const
//        {
//            return m_credentials;
//        }
   
//        void set_credentials(const http::client::credentials& cred)
//        {
//            m_credentials = cred;
//        }
   
//        bool guarantee_order() const
//        {
//            return m_guarantee_order;
//        }
   
//        CASABLANCA_DEPRECATED("Confusing API will be removed in future releases. If you need to order HTTP requests use task continuations.")
//        void set_guarantee_order(bool guarantee_order)
//        {
//            m_guarantee_order = guarantee_order;
//        }
   
//        utility::seconds timeout() const
//        {
//            return std::chrono::duration_cast<utility::seconds>(m_timeout);
//        }
   
//        template <class T>
//        T timeout() const
//        {
//            return std::chrono::duration_cast<T>(m_timeout);
//        }
//        template <class T>
//        void set_timeout(const T &timeout)
//        {
//            m_timeout = std::chrono::duration_cast<std::chrono::microseconds>(timeout);
//        }
   
//        size_t chunksize() const
//        {
//            return m_chunksize == 0 ? 64 * 1024 : m_chunksize;
//        }
   
//        void set_chunksize(size_t size)
//        {
//            m_chunksize = size;
//        }
   
//        bool is_default_chunksize() const
//        {
//            return m_chunksize == 0;
//        }
   
//    #if !defined(__cplusplus_winrt)
//        bool validate_certificates() const
//        {
//            return m_validate_certificates;
//        }
   
//        void set_validate_certificates(bool validate_certs)
//        {
//            m_validate_certificates = validate_certs;
//        }
//    #endif
   
//    #ifdef _WIN32
//    #if !defined(__cplusplus_winrt)
//        bool buffer_request() const
//        {
//            return m_buffer_request;
//        }
   
//        void set_buffer_request(bool buffer_request)
//        {
//            m_buffer_request = buffer_request;
//        }
//    #endif
//    #endif
   
//        void set_nativehandle_options(const std::function<void(native_handle)> &callback)
//        {
//             m_set_user_nativehandle_options = callback;
//        }
   
//        void invoke_nativehandle_options(native_handle handle) const
//        {
//            m_set_user_nativehandle_options(handle);
//        }
   
//    #if !defined(_WIN32) && !defined(__cplusplus_winrt)
//        void set_ssl_context_callback(const std::function<void(boost::asio::ssl::context&)>& callback)
//        {
//             m_ssl_context_callback = callback;
//        }
   
//        const std::function<void(boost::asio::ssl::context&)>& get_ssl_context_callback() const
//        {
//            return m_ssl_context_callback;
//        }
//    #endif
   
//    private:
//    #if !defined(CPPREST_TARGET_XP)
//        std::shared_ptr<oauth1::experimental::oauth1_config> m_oauth1;
//    #endif
   
//        std::shared_ptr<oauth2::experimental::oauth2_config> m_oauth2;
//        web_proxy m_proxy;
//        http::client::credentials m_credentials;
//        // Whether or not to guarantee ordering, i.e. only using one underlying TCP connection.
//        bool m_guarantee_order;
   
//        std::chrono::microseconds m_timeout;
//        size_t m_chunksize;
   
//    #if !defined(__cplusplus_winrt)
//        // IXmlHttpRequest2 doesn't allow configuration of certificate verification.
//        bool m_validate_certificates;
//    #endif
   
//        std::function<void(native_handle)> m_set_user_nativehandle_options;
   
//    #if !defined(_WIN32) && !defined(__cplusplus_winrt)
//        std::function<void(boost::asio::ssl::context&)> m_ssl_context_callback;
//    #endif
//    #if defined(_WIN32) && !defined(__cplusplus_winrt)
//        bool m_buffer_request;
//    #endif
//    };
   
//    class http_client
//    {
//    public:
//        _ASYNCRTIMP http_client(const uri &base_uri);
   
//        _ASYNCRTIMP http_client(const uri &base_uri, const http_client_config &client_config);
   
//        ~http_client() CPPREST_NOEXCEPT {}
   
//        _ASYNCRTIMP const uri& base_uri() const;
   
//        _ASYNCRTIMP const http_client_config& client_config() const;
   
//        void add_handler(const std::function<pplx::task<http_response>(http_request, std::shared_ptr<http::http_pipeline_stage>)> &handler)
//        {
//            m_pipeline->append(std::make_shared<::web::http::details::function_pipeline_wrapper>(handler));
//        }
   
//        void add_handler(const std::shared_ptr<http::http_pipeline_stage> &stage)
//        {
//            m_pipeline->append(stage);
//        }
   
//        _ASYNCRTIMP pplx::task<http_response> request(http_request request, const pplx::cancellation_token &token = pplx::cancellation_token::none());
   
//        pplx::task<http_response> request(const method &mtd, const pplx::cancellation_token &token = pplx::cancellation_token::none())
//        {
//            http_request msg(mtd);
//            return request(msg, token);
//        }
   
//        pplx::task<http_response> request(
//            const method &mtd,
//            const utility::string_t &path_query_fragment,
//            const pplx::cancellation_token &token = pplx::cancellation_token::none())
//        {
//            http_request msg(mtd);
//            msg.set_request_uri(path_query_fragment);
//            return request(msg, token);
//        }
   
//        pplx::task<http_response> request(
//            const method &mtd,
//            const utility::string_t &path_query_fragment,
//            const json::value &body_data,
//            const pplx::cancellation_token &token = pplx::cancellation_token::none())
//        {
//            http_request msg(mtd);
//            msg.set_request_uri(path_query_fragment);
//            msg.set_body(body_data);
//            return request(msg, token);
//        }
   
//        pplx::task<http_response> request(
//            const method &mtd,
//            const utf8string &path_query_fragment,
//            const utf8string &body_data,
//            const utf8string &content_type = "text/plain; charset=utf-8",
//            const pplx::cancellation_token &token = pplx::cancellation_token::none())
//        {
//            http_request msg(mtd);
//            msg.set_request_uri(::utility::conversions::to_string_t(path_query_fragment));
//            msg.set_body(body_data, content_type);
//            return request(msg, token);
//        }
   
//        pplx::task<http_response> request(
//            const method &mtd,
//            const utf8string &path_query_fragment,
//            utf8string &&body_data,
//            const utf8string &content_type = "text/plain; charset=utf-8",
//            const pplx::cancellation_token &token = pplx::cancellation_token::none())
//        {
//            http_request msg(mtd);
//            msg.set_request_uri(::utility::conversions::to_string_t(path_query_fragment));
//            msg.set_body(std::move(body_data), content_type);
//            return request(msg, token);
//        }
   
//        pplx::task<http_response> request(
//            const method &mtd,
//            const utf16string &path_query_fragment,
//            const utf16string &body_data,
//            const utf16string &content_type = ::utility::conversions::to_utf16string("text/plain"),
//            const pplx::cancellation_token &token = pplx::cancellation_token::none())
//        {
//            http_request msg(mtd);
//            msg.set_request_uri(::utility::conversions::to_string_t(path_query_fragment));
//            msg.set_body(body_data, content_type);
//            return request(msg, token);
//        }
   
//        pplx::task<http_response> request(
//            const method &mtd,
//            const utf8string &path_query_fragment,
//            const utf8string &body_data,
//            const pplx::cancellation_token &token)
//        {
//            return request(mtd, path_query_fragment, body_data, "text/plain; charset=utf-8", token);
//        }
   
//        pplx::task<http_response> request(
//            const method &mtd,
//            const utf8string &path_query_fragment,
//            utf8string &&body_data,
//            const pplx::cancellation_token &token)
//        {
//            http_request msg(mtd);
//            msg.set_request_uri(::utility::conversions::to_string_t(path_query_fragment));
//            msg.set_body(std::move(body_data), "text/plain; charset=utf-8");
//            return request(msg, token);
//        }
   
//        pplx::task<http_response> request(
//            const method &mtd,
//            const utf16string &path_query_fragment,
//            const utf16string &body_data,
//            const pplx::cancellation_token &token)
//        {
//            return request(mtd, path_query_fragment, body_data, ::utility::conversions::to_utf16string("text/plain"), token);
//        }
   
//    #if !defined (__cplusplus_winrt)
//        pplx::task<http_response> request(
//            const method &mtd,
//            const utility::string_t &path_query_fragment,
//            const concurrency::streams::istream &body,
//            const utility::string_t &content_type = _XPLATSTR("application/octet-stream"),
//            const pplx::cancellation_token &token = pplx::cancellation_token::none())
//        {
//            http_request msg(mtd);
//            msg.set_request_uri(path_query_fragment);
//            msg.set_body(body, content_type);
//            return request(msg, token);
//        }
   
//        pplx::task<http_response> request(
//            const method &mtd,
//            const utility::string_t &path_query_fragment,
//            const concurrency::streams::istream &body,
//            const pplx::cancellation_token &token)
//        {
//            return request(mtd, path_query_fragment, body, _XPLATSTR("application/octet-stream"), token);
//        }
//    #endif // __cplusplus_winrt
   
//        pplx::task<http_response> request(
//            const method &mtd,
//            const utility::string_t &path_query_fragment,
//            const concurrency::streams::istream &body,
//            size_t content_length,
//            const utility::string_t &content_type = _XPLATSTR("application/octet-stream"),
//            const pplx::cancellation_token &token = pplx::cancellation_token::none())
//        {
//            http_request msg(mtd);
//            msg.set_request_uri(path_query_fragment);
//            msg.set_body(body, content_length, content_type);
//            return request(msg, token);
//        }
   
//        pplx::task<http_response> request(
//            const method &mtd,
//            const utility::string_t &path_query_fragment,
//            const concurrency::streams::istream &body,
//            size_t content_length,
//            const pplx::cancellation_token &token)
//        {
//            return request(mtd, path_query_fragment, body, content_length, _XPLATSTR("application/octet-stream"), token);
//        }
   
//    private:
   
//        void build_pipeline(const uri &base_uri, const http_client_config &client_config);
   
//        std::shared_ptr<::web::http::http_pipeline> m_pipeline;
//    };
   
//    }}}
   
//    #endif