#include"DataStream.h"
#include<fstream>
using namespace serialize;
void DataStream::reserve(int len)
{
	int size = m_buf.size();
	int cap = m_buf.capacity();
	if ((len + size) > cap)
	{
		while ((len + size) > cap)
		{
			if (cap == 0)
			{
				cap = 1;
			}
			else
			{
				cap *= 2;
			}
		}
		m_buf.reserve(cap);
	}
}
void DataStream::show() const
{
	int size = m_buf.size();
	std::cout << "data size: " << size << std::endl;
	int i = 0;
	while (i < size)
	{
		switch ((DataType)m_buf[i])
		{
		case DataType::BOOL:
			if ((int)m_buf[++i] == 0)
			{
				std::cout << "false" << std::endl;
			}
			else
			{
				std::cout << "true" << std::endl;
			}
			++i;
			break;
		case DataType::CHAR:
			std::cout << m_buf[++i] << std::endl;
			++i;
			break;
		case DataType::INT_32:
			std::cout << *((int32_t*)&m_buf[++i]) << std::endl;
			i += 4;
			break;
		case DataType::INT_64:
			std::cout << *((int64_t*)&m_buf[++i]) << std::endl;
			i += 8;
			break;
		case DataType::FLOAT:
			std::cout << *((float*)&m_buf[++i]) << std::endl;
			i += 4;
			break;
		case DataType::DOUBLE:
			std::cout << *((double*)&m_buf[++i]) << std::endl;
			i += 8;
			break;
		case DataType::STRING:
			if ((DataType)m_buf[++i] == DataType::INT_32)
			{
				int len = *((int32_t*)&m_buf[++i]);
				i += 4;
				std::cout << std::string(&m_buf[i], len) << std::endl;
				i += len;
			}
			break;
		default:
			break;
		}
	}
}
void DataStream::write(const char* data, int len)
{
	reserve(len);
	int size = m_buf.size();
	m_buf.resize(size + len);
	std::memcpy(&m_buf[size], data, len);
	

}
void  DataStream::write(bool value)
{
	char type = DataType::BOOL;
	write((char*)&type, sizeof(char));
	write((char*)&value, sizeof(char));
}
void  DataStream::write(char value)
{
	char type = DataType::CHAR;
	write((char*)&type, sizeof(char));
	write((char*)&value, sizeof(char));
}
void  DataStream::write(int32_t value)
{
	char type = DataType::INT_32;
	write((char*)&type, sizeof(char));
	write((char*)&value, sizeof(int32_t));
}
void  DataStream::write(int64_t value)
{
	char type = DataType::INT_64;
	write((char*)&type, sizeof(char));
	write((char*)&value, sizeof(int64_t));
}
void  DataStream::write(float value)
{
	char type = DataType::FLOAT;
	write((char*)&type, sizeof(char));
	write((char*)&value, sizeof(float));
}
void  DataStream::write(double value)
{
	char type = DataType::DOUBLE;
	write((char*)&type, sizeof(char));
	write((char*)&value, sizeof(double));
}
void DataStream::write(const char* value)
{
	char type = DataType::STRING;
	write((char*)&type, sizeof(char));
	int len = strlen(value);
	write(len);
	write(value, len);
}
void DataStream::write(const string& value)
{
	char type = DataType::STRING;
	write((char*)&type, sizeof(char));
	int len = value.size();
	write(len);
	write(value.data(), len);
}

bool DataStream::read(bool& value)
{
	if (m_buf[m_pos] != DataType::BOOL)
	{
		return false;
	}
	else
	{
		++m_pos;
		value = m_buf[m_pos];
		++m_pos;
		return true;
	}
}
bool DataStream::read(char& value)
{
	if (m_buf[m_pos] != DataType::CHAR)
	{
		return false;
	}
	else
	{
		++m_pos;
		value = m_buf[m_pos];
		++m_pos;
		return true;
	}
}
bool DataStream::read(int32_t& value)
{
	if (m_buf[m_pos] != DataType::INT_32)
	{
		return false;
	}
	else
	{
		++m_pos;
		value = *((int32_t*)&m_buf[m_pos]);
		m_pos += 4;
		return true;
	}
}
bool DataStream::read(int64_t& value)
{
	if (m_buf[m_pos] != DataType::INT_64)
	{
		return false;
	}
	else
	{
		value = *((int64_t*)&m_buf[++m_pos]);
		m_pos += 8;
		return true;
	}
}
bool DataStream::read(float& value)
{
	if (m_buf[m_pos] != DataType::FLOAT)
	{
		return false;
	}
	else
	{
		value = *((float*)&m_buf[++m_pos]);
		m_pos += 4;
		return true;
	}
}
bool DataStream::read(double& value)
{
	if (m_buf[m_pos] != DataType::DOUBLE)
	{
		return false;
	}
	else
	{
		value = *((double*)&m_buf[++m_pos]);
		m_pos += 8;
		return true;
	}
}
bool DataStream::read(char*& value)
{
	if (m_buf[m_pos] != DataType::STRING)
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
		memcpy(value, &m_buf[m_pos], len);
		m_pos += len;
		return true;
	}
}
bool DataStream::read(string& value)
{
	if (m_buf[m_pos] != DataType::STRING)
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
		value.assign((char*)&m_buf[m_pos], len);
		m_pos += len;
		return true;
	}
}
DataStream& DataStream::operator << (bool value)
{
	write(value);
	return *this;
}
DataStream& DataStream::operator << (char value)
{
	write(value);
	return *this;
}

DataStream& DataStream::operator << (int32_t value)
{
	write(value);
	return *this;
}

DataStream& DataStream::operator << (int64_t value)
{
	write(value);
	return *this;
}

DataStream& DataStream::operator << (float value)
{
	write(value);
	return *this;
}

DataStream& DataStream::operator << (double value)
{
	write(value);
	return *this;
}

DataStream& DataStream::operator << (const char* value)
{
	write(value);
	return *this;
}

DataStream& DataStream::operator << (const string& value)
{
	write(value);
	return *this;
}

DataStream& DataStream::operator >> (bool& value)
{
	read(value);
	return *this;
}
DataStream& DataStream::operator >> (char& value)
{
	read(value);
	return *this;
}

DataStream& DataStream::operator >> (int32_t& value)
{
	read(value);
	return *this;
}

DataStream& DataStream::operator >> (int64_t& value)
{
	read(value);
	return *this;
}

DataStream& DataStream::operator >> (float& value)
{
	read(value);
	return *this;
}

DataStream& DataStream::operator >> (double& value)
{
	read(value);
	return *this;
}

DataStream& DataStream::operator >> ( char*& value)
{
	read(value);
	return *this;
}

DataStream& DataStream::operator >> ( string& value)
{
	read(value);
	return *this;
}

bool DataStream::save(const string& name)
{
	ofstream out;
	out.open(name, ios::out | ios::binary | ios::trunc);
	if (out.is_open())
	{
		int size = m_buf.size();
		char* buf = new char[size];
		memcpy(buf, &m_buf[0], size);
		out.write(buf, size);
		delete[] buf;
	}
	else
	{
		return false;
	}
	out.close();
	
	return true;
}

bool DataStream::save(const char* name)
{
	ofstream out;
	out.open(name, ios::out | ios::binary | ios::trunc);
	if (out.is_open())
	{
		int size = m_buf.size();
		char* buf = new char[size];
		memcpy(buf, &m_buf[0], size);
		out.write(buf, size);
		delete[] buf;
	}
	else
	{
		return false;
	}
	out.close();
	return true;
}

bool DataStream::open(const string& name)
{
	ifstream in(name,ios::in | ios::binary);
	if (in.is_open())
	{
		int start = in.tellg();
		in.seekg(0, ios::end);
		int end = in.tellg();
		int size = end - start;
		in.seekg(0, ios::beg);
		cout << size << endl;
		reserve(size);
		m_buf.resize(size);
		in.seekg(0, ios::beg);
		char* buf = new char[size];
		in.read(buf, size);
		std::memcpy(&m_buf[0], buf, size);
		delete[] buf;

	}
	else
	{
		return false;
	}
	in.close();
	return true;
}
bool DataStream::open(const char* name)
{
	ifstream in(name, ios::in | ios::binary);
	if (in.is_open())
	{
		int start = in.tellg();
		in.seekg(0, ios::end);
		int end = in.tellg();
		int size = end - start;
		in.seekg(0, ios::beg);
		cout << size << endl;
		reserve(size);
		m_buf.resize(size);
		in.seekg(0, ios::beg);
		char* buf = new char[size];
		in.read(buf, size);
		std::memcpy(&m_buf[0], buf, size);
		delete[] buf;
	}
	else
	{
		return false;
	}
	in.close();
	return true;
}

