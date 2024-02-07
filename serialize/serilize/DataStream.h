#pragma once
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
using namespace std;
namespace serialize
{

	class DataStream
	{
	public:
		DataStream():m_pos(0){};
		~DataStream() {};
	private:
		std::vector<char> m_buf;
		int m_pos;
	private:
		void reserve(int len);
	public:
		enum DataType
		{
			BOOL=0,
			CHAR,
			INT_32,
			INT_64,
			FLOAT,
			DOUBLE,
			STRING,
			VECTOR,
			SET,
			MAP,
			CUSTOM

		};
		void show() const;
		void write(const char* data, int len);
		void write(bool value);
		void write(char value);
		void write(int32_t value);
		void write(int64_t value);
		void write(float value);
		void write(double value);
		void write(const char* value);
		void write(const string& value);

		bool read(bool& value);
		bool read(char& value);
		bool read(int32_t& value);
		bool read(int64_t& value);
		bool read(float& value);
		bool read(double& value);
		bool read(char*& value);
		bool read(string& value);

		DataStream& operator << (bool value);
		DataStream& operator << (char value);
		DataStream& operator << (int32_t value);
		DataStream& operator << (int64_t value);
		DataStream& operator << (float value);
		DataStream& operator << (double value);
		DataStream& operator << (const char* value);
		DataStream& operator << (const string& value);

		DataStream& operator >> (bool&value);
		DataStream& operator >> (char&value);
		DataStream& operator >> (int32_t& value);
		DataStream& operator >> (int64_t& value);
		DataStream& operator >> (float& value);
		DataStream& operator >> (double& value);
		DataStream& operator >> (char*& value);
		DataStream& operator >> (string& value);

		bool save(const string& name);
		bool save(const char* name);

		bool open(const string& name);
		bool open(const char* name);
	};
	
}
