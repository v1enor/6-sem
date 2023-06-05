#include "pch.h"
#include "HTHandle.h"

HTHANDLE::HTHANDLE()
	:Capacity{0}, SecSnapshotInterval{0}, MaxKeyLength{0}, MaxPayloadLength{0}, FileName{NULL}
{}

HTHANDLE::HTHANDLE(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const wchar_t FileName[512])
{
	this->Capacity = Capacity;
	this->SecSnapshotInterval = SecSnapshotInterval;
	this->MaxKeyLength = MaxKeyLength;
	this->MaxPayloadLength = MaxPayloadLength;
	this->N = 0;
	memcpy(this->FileName, FileName, sizeof(this->FileName));
}

Element::Element()
{
	this->key = nullptr;
	this->keylength = NULL;
	this->payload = nullptr;
	this->payloadlength = NULL;
}

Element::Element(const void* key, int keylength)
{
	Element();
	this->key = (void*)key;
	this->keylength = keylength;
}

Element::Element(const void* key, int keylength, const void* payload, int  payloadlength)
{
	this->key = (void*)key;
	this->keylength = keylength;
	this->payload = (void*)payload;
	this->payloadlength = payloadlength;
}

Element::Element(Element* oldelement, const void* newpayload, int  newpayloadlength)
{
	this->key = oldelement->key;
	this->keylength = oldelement->keylength;
	this->payload = (void*)payload;
	this->payloadlength = payloadlength;
}
