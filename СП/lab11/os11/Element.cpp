#include "Element.h"
#include <Windows.h>

namespace HT
{
	Element::Element()
	{
		this->m_KeyLength = 0;
		this->m_Key = nullptr;

		this->m_ValueLength = 0;
		this->m_Value = nullptr;
	}

	Element::Element(const char* inKey, int inKeyLength, const char* inValue, int  inValueLength)
	{
		this->SetKey(inKey, inKeyLength);
		this->SetValue(inValue, inValueLength);
	}

	const char* Element::GetKey() const
	{
		return this->m_Key;
	}

	void Element::SetKey(const char* inKey, const int inKeyLength)
	{
		for (int i = 0; i < inKeyLength; i++)
		{
			this->m_Key[i] = inKey[i];
		}

		this->m_KeyLength = inKeyLength;
	}

	void Element::SetKeyPointer(char* inKeyPoint)
	{
		this->m_Key = inKeyPoint;
	}

	void Element::ClearKey()
	{
		ZeroMemory(this->m_Key, m_KeyLength);
		m_KeyLength = 0;
	}

	const int Element::GetKeyLength() const
	{
		return this->m_KeyLength;
	}

	const char* Element::GetValue() const
	{
		return this->m_Value;
	}

	void Element::SetValue(const char* inValue, const int inValueLength)
	{
		for (int i = 0; i < inValueLength; i++)
		{
			this->m_Value[i] = inValue[i];
		}

		this->m_ValueLength = inValueLength;
	}

	void Element::SetValuePointer(char* inValuePoint)
	{
		this->m_Value = inValuePoint;
	}

	void Element::ClearValue()
	{
		ZeroMemory(this->m_Value, m_ValueLength);
		m_ValueLength = 0;
	}

	const int Element::GetValueLength() const
	{
		return this->m_ValueLength;
	}

}

