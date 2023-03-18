// pch.h
// (C) Martin Alebachew, 2023

#pragma once
#include <iostream>
#include <vector>
#include <fstream>

// Project Dependencies
#include <curl/curl.h>
#include <json/json.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

// WinAPI
#include <Windows.h>
#include <tlhelp32.h>