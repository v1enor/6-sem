#include "Service.h"

void main()
{
	WCHAR ServiceName[] = SERVICENAME;

	SERVICE_TABLE_ENTRY ServiceStartTable[] = {
		{ServiceName, ServiceMain},
		{NULL, NULL}
	};

	if (!StartServiceCtrlDispatcher(ServiceStartTable))
		trace("StartServiceCtrlDispatcher", std::ofstream::out);
}