#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
#include "UnbanMii.h"


u32 CalculateNwc24ConfigChecksum(nwc24_config_t config)
	{
		u32* ptr = (u32*)&config;
		u32 sum = 0;
		int i;
		for (i=0; i<0xFF; i++)
		{
			sum += _byteswap_ulong (*ptr++);
		}
		return sum;
	}


int _tmain(int argc, _TCHAR* argv[])
{
	if (argc != 2)
	{
		std::cout << "no file specified";
		return 0;
	}

	std::wstring filename = argv[1];

	if (filename.find(L"nwc24msg.cfg") == std::string::npos)
	{
		std::cout << "File isn't nwc24msg.cfg";
		return 0;
	}

	std::fstream file;

	file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
	if (file.is_open())
	{
		srand(time(NULL));

		nwc24_config_t config;
		file.seekg (0);
		file.read((char*)&config, 1024);

		u8* id = (u8*)&config.nwc24_id;
		for (int i = 0; i < 8; ++i, ++id)
			*id = rand();
		config.checksum = CalculateNwc24ConfigChecksum(config);
		file.seekg (0);
		file.write((char*)&config, 1024);

		file.close();
		std::cout << "New ID generated successfully.";
	}
	else
		std::cout << "Failed to open file.";

	return 0;
}
