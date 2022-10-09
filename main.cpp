#include <Windows.h>
#include <iostream>
using namespace std;

class WrapperHandle {
public:
	WrapperHandle() = default;


	WrapperHandle(LPCSTR src, LPCSTR dest) {
		Set(src, dest);
	}

	void Clean() {
		CloseHandle(m_src);
		m_src = nullptr;
		CloseHandle(m_dest);
		m_dest = nullptr;
	}

	void Set(LPCSTR src, LPCSTR dest) {
		if (m_src != nullptr && m_dest != nullptr) {
			Clean();
		}

		m_src = CreateFileA(
			src,
			GENERIC_READ,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			0
		);

		if (m_src == INVALID_HANDLE_VALUE) {
			throw runtime_error("INVALID_HANDLE_VALUE of src.");
		}

		m_dest = CreateFileA(
			dest,
			GENERIC_WRITE,
			0,
			0,
			TRUNCATE_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			0
		);

		if (m_dest == INVALID_HANDLE_VALUE) {
			throw runtime_error("Error! I can't create file.");
		}
	}

	void Copy() {
		const int bufferSize = 1024;
		char buffer[bufferSize];
		DWORD bytesRead = 0;
		BOOL res = ReadFile(m_src, &buffer, bufferSize - 1, &bytesRead, NULL);
		if (!res) {
			throw runtime_error("I can't read this file");
		}

		res = WriteFile(
			m_dest,
			buffer,
			bytesRead,
			0,
			0
		);

		if (res == false) {
			throw runtime_error("I can't write this file");
		}
	}

	~WrapperHandle() {
		if (m_dest && m_src) {
			Clean();
		}
	}

private:
	HANDLE m_src = nullptr;
	HANDLE m_dest = nullptr;
};


int main(int argc, char* argv[]) {
	/*if (argc < 3) {
		cerr << "Not enough arg ERROR!!\n";
		return -1;
	}
	for (size_t i = 0; i < argc; i++)
	{
		cout << argv[i] << endl;
	}*/

	//WrapperHandle wrapper("D:\\projects\\cplus\\Apriorit\\WrapperForCopyFile\\Debug\\from.txt", "dest.txt");
	
	/*HANDLE hout = CreateFileA("D:\\projects\\cplus\\Apriorit\\WrapperForCopyFile\\Debug\\from.txt", 
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		0
	);

	if (hout == INVALID_HANDLE_VALUE)
	{
		cout << "error";
	}

	const int bufferSize = 1024;
	char buffer[bufferSize];
	DWORD bytesRead = 0;
	BOOL res = ReadFile(hout, &buffer, bufferSize - 1, &bytesRead, NULL);
	if (!res) {
		cerr << "I can't read\n";
		return -1;
	}

	cout << bytesRead << endl;
	cout << buffer << endl;

	HANDLE hin = CreateFileA(
		"D:\\projects\\cplus\\Apriorit\\WrapperForCopyFile\\Debug\\to.txt",
		GENERIC_WRITE,
		0,
		0,
		TRUNCATE_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		0
	);

	if (hin == INVALID_HANDLE_VALUE) {
		cerr << "Error! I can't create file\n";
		return -1;
	}

	res = WriteFile(
		hin,
		buffer,
		bytesRead,
		0,
		0
	);
	if (res == false) {
		return -2;
	}*/

	WrapperHandle wrapper;
	const char* src = "D:\\projects\\cplus\\Apriorit\\WrapperForCopyFile\\Debug\\from.txt";
	const char* dest = "D:\\projects\\cplus\\Apriorit\\WrapperForCopyFile\\Debug\\to.txt";
	wrapper.Set(src, dest);
	wrapper.Copy();
	return 0;
}