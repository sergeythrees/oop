﻿// task1tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../HttpUrl/HttpUrl.h"

BOOST_AUTO_TEST_SUITE(HttpUrl_class)

	BOOST_AUTO_TEST_CASE(can_be_costruct_from_url_string)
	{
		CHttpUrl url("http://www.mysite.com:100/docs/document1.html?page=30&lang=en#title");
		BOOST_CHECK(url.IsInitialized());
		BOOST_CHECK_EQUAL(url.port(), 100);
	}

	BOOST_AUTO_TEST_CASE(can_be_costruct_from_url_without_port_value)
	{
		CUrl url("http://www.mysite.com/docs/document1.html?page=30&lang=en#title");
		BOOST_CHECK(url.IsInitialized());
		BOOST_CHECK_EQUAL(url.port(), 80);
	}

	BOOST_AUTO_TEST_CASE(can_be_costruct_from_url_with_other_protocol)
	{
		CUrl httpsUrl("https://www.mysite.com/docs/document1.html?page=30&lang=en#title");
		BOOST_CHECK(httpsUrl.IsInitialized());
		BOOST_CHECK(httpsUrl.protocol() == Protocol::HTTPS);

		CUrl ftpUrl("ftp://www.mysite.com/docs/document1.html?page=30&lang=en#title");
		BOOST_CHECK(ftpUrl.IsInitialized());
		BOOST_CHECK(ftpUrl.protocol() == Protocol::FTP);
	}

	BOOST_AUTO_TEST_CASE(can_be_constructed_from_input_parameters)
	{
		CHttpUrl test("domain", "document", HTTPS);
		BOOST_CHECK(true);
	}

	BOOST_AUTO_TEST_CASE(can_be_constructed_from_url_string)
	{
		CHttpUrl test("https://google.com/mail/index.html");
		BOOST_CHECK_EQUAL(test.GetPort(), 80);
		BOOST_CHECK_EQUAL(test.GetProtocol(), HTTPS);
	}
	BOOST_AUTO_TEST_SUITE(while_constructing)
		BOOST_AUTO_TEST_CASE(verify_domain)
		{
			CHttpUrl test("domain", "document", HTTPS);
			BOOST_CHECK(true);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct HttpUrlFixture
	{
		CHttpUrl test;
		HttpUrlFixture()
			: test("google.com", "/mail/index.html", HTTPS)
		{}

	
	};

	BOOST_FIXTURE_TEST_SUITE(after_construction, HttpUrlFixture)
		BOOST_AUTO_TEST_CASE(can_get_domain)
		{
			BOOST_CHECK_EQUAL(test.GetDomain(), "google.com");
		}
		BOOST_AUTO_TEST_CASE(can_get_document)
		{
			BOOST_CHECK_EQUAL(test.GetDocument(), "/mail/index.html");
		}
		BOOST_AUTO_TEST_CASE(can_get_protocol)
		{
			BOOST_CHECK_EQUAL(test.GetProtocol(), HTTPS);
		}
		BOOST_AUTO_TEST_CASE(can_get_port)
		{
			BOOST_CHECK_EQUAL(test.GetPort(), 80);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()

