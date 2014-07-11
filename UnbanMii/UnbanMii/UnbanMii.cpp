#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
#include "UnbanMii.h"
#include <ShlObj.h>


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

	std::wstring filename;
	if (argc != 2)
	{
		std::ifstream file(L"nwc24msg.cfg");

		std::ifstream global_file;
		bool global_exists = false;

		WCHAR my_documents[MAX_PATH];
		bool my_documents_found = SUCCEEDED(SHGetFolderPath(nullptr, CSIDL_MYDOCUMENTS, nullptr, SHGFP_TYPE_CURRENT, my_documents));
		if (my_documents_found)
		{
			global_file.open(std::wstring(my_documents) + L"/Dolphin Emulator/Wii/shared2/wc24/nwc24msg.cfg");
			if (global_file.is_open())
				global_exists = true;
		}


		if (file.is_open())
		{
			std::cout << "Using nwc24msg.cfg in current directory.\n";
			filename = L"nwc24msg.cfg";
		}
		else if (global_exists)
		{
			std::cout << "Using nwc24msg.cfg in global user directory.\n";
			filename = std::wstring(my_documents) + L"/Dolphin Emulator/Wii/shared2/wc24/nwc24msg.cfg";
		}
		else
		{
			std::cout << "no file specified";
			return 0;
		}
	}
	else
		filename = argv[1];

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
