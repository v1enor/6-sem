#pragma once


namespace HT
{
	/**
	* Element of อา-storage consist from key-value pair
	*/
	class Element
	{
	public:

		/**
		* Using just for initialize of empty element
		*/
		Element();

		/**
		* Full constructor
		*/
		Element(const char* inKey, int inKeyLength, const char* inValue, int  inValueuLength);

		/**
		* Reference of Element key in memory
		*/
		const char* GetKey() const;

		/**
		* Change reference of Element key in memory and it's length
		*/
		void SetKey(const char* inKey, const int inKeyLength);

		/**
		* Set key pointer in the memory
		*/
		void SetKeyPointer(char* inKeyPoint);

		/**
		* Clear key memory space
		*/
		void ClearKey();

		/**
		* Count of bytes which are used by Element key in memory
		*/
		const int GetKeyLength() const;

		/**
		* Reference of Element value in memory
		*/
		const char* GetValue() const;

		/**
		* Change reference of Element value in memory and it's length
		*/
		void SetValue(const char* inValue, const int inValueLength);

		/**
		* Set value pointer in the memory
		*/
		void SetValuePointer(char* inValuePoint);

		/**
		* Clear key memory space
		*/
		void ClearValue();

		/**
		* Count of bytes which are used by Element value in memory
		*/
		const int GetValueLength() const;

	private:

		char* m_Key;
		int	m_KeyLength;
		char* m_Value;
		int	m_ValueLength;
	};
}