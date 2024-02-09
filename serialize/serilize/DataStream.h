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
			CUSTOM,
			TYPE
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
		template <class T>
		void write(T value)
		{
			char type = DataType::TYPE;
			write((char*)&type, sizeof(char));
			int len =sizeof(value);
			write(len);
			write((char*)&value, len);
		}
		
		bool read(bool& value);
		bool read(char& value);
		bool read(int32_t& value);
		bool read(int64_t& value);
		bool read(float& value);
		bool read(double& value);
		bool read(char*& value);
		bool read(string& value);
		template <class T>
		bool read(T &value)
		{
			if (m_buf[m_pos] != DataType::TYPE)
			{
				return false;
			}
			else
			{
				++m_pos;
				int len;
				read(len);
				if (len < 0)
					return false;
				memcpy((void*)&value, &m_buf[m_pos], len);
				m_pos += len;
				return true;
			}
		}

		DataStream& operator << (bool value);
		DataStream& operator << (char value);
		DataStream& operator << (int32_t value);
		DataStream& operator << (int64_t value);
		DataStream& operator << (float value);
		DataStream& operator << (double value);
		DataStream& operator << (const char* value);
		DataStream& operator << (const string& value);
		template <class T>
		DataStream& operator << (const T& value)
		{
			write(value);
			return *this;
		}

		DataStream& operator >> (bool&value);
		DataStream& operator >> (char&value);
		DataStream& operator >> (int32_t& value);
		DataStream& operator >> (int64_t& value);
		DataStream& operator >> (float& value);
		DataStream& operator >> (double& value);
		DataStream& operator >> (char*& value);
		DataStream& operator >> (string& value);
		template <class T>
		DataStream& operator >> (const T& value)
		{
			read(value);
			return *this;
		}

		bool save(const string& name);
		bool save(const char* name);

		bool open(const string& name);
		bool open(const char* name);
	};
	
}
