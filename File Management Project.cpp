
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

void WriteIntoFile(string&);

string GetFileName(string Message)
{
	string FileName;

	cout << Message;
	cin >> FileName;

	return FileName;
}

string GetRecord(string Message)
{
	string Record;

	cout << Message;
	getline(cin, Record);

	return Record;
}

short GetTaskNumber()
{
	short TaskNumber = 0;

	do
	{

		cout << "\nPlease Enter the Task Number : ";
		cin >> TaskNumber;

	} while (TaskNumber < 1 || TaskNumber > 6);

	return TaskNumber;
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

int ReadFilesNumber()
{
	int FilesNumber = 0;

	cout << "\nPlease Enter the Number of Files : ";
	cin >> FilesNumber;

	return FilesNumber;
}

void CheckWriting()
{
	string* FileName;
	FileName = new string;

	*FileName = GetFileName("\nEnter the File Name and Extension : ");

	char WriteIntoFile1 = 'Y';

	fstream MyFile;
	MyFile.open(*FileName, ios::app);

	if (WriteIntoFile1 == 'Y' || WriteIntoFile1 == 'y')
	{
		WriteIntoFile(*FileName);
		MyFile.close();
	}
	else
	{
		MyFile.close();
	}

	delete FileName;

}

void WriteIntoFile(string& FileName)
{
	string* Text;
	char* AddMore;

	Text = new string;
	AddMore = new char;

	*AddMore = 'Y';
	fstream MyFile;

	MyFile.open(FileName, ios::app);

	while (*AddMore == 'Y' || *AddMore == 'y')
	{

		cout << "\nPlease Enter the Text : " << endl;
		cin.ignore(1, '\n');
		getline(cin, *Text);

		MyFile << *Text << endl;

		cout << "\nDo you Want to Add more text? Y/N? ";
		cin >> *AddMore;

	}

	delete Text;
	delete AddMore;
}

void PrintFileContent(string &FileName)
{
	
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string* Line;
		Line = new string;

		cout << "\n_________________" << FileName << " Content_________________\n\n";

		while (getline(MyFile, *Line))
		{
			cout << *Line << endl;
		}

		cout << "_________________________________________________\n";

		MyFile.close();

		delete Line;
	}
}

void CheckPrintingContent()
{
	string* FileName;
	char* PrintContent;

	FileName = new string;
	PrintContent = new char;

	*PrintContent = 'Y';

	while (*PrintContent == 'Y' || *PrintContent == 'y')
	{
		ResetScreen();
		*FileName = GetFileName("Please Enter The File Name and Extension : ");
		PrintFileContent(*FileName);

		cout << "\nDo You Want to Print another File Content? Y/N? ";
		cin >> *PrintContent;
	}

	delete FileName;
	delete PrintContent;
}

void CreateFiles()
{
	int* FilesNumber;
	string* FileName;

	FilesNumber = new int;
	FileName = new string;

	*FilesNumber = ReadFilesNumber();

	fstream MyFile;

	for (int i = 1; i <= *FilesNumber; i++)
	{
		cout << "\n___________________________File [" << i << "]___________________________\n\n";

		*FileName = GetFileName("Please Enter The File Name and Extension : ");

		MyFile.open(*FileName, ios::out);
		MyFile.close();

		cout << "\n__________________" << *FileName << " Created Successfully__________________";

		cout << "\a\n\n";
	}

	delete FilesNumber;
	delete FileName;
}

void LoadDataFromFileToVector(string& FileName, vector<string>& vFileContent)
{
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string* Line;
		Line = new string;

		while (getline(MyFile, *Line))
		{
			vFileContent.push_back(*Line);
		}

		MyFile.close();

		delete Line;
	}
}

void SaveVectorToFile(string& FileName, vector<string>& vFileContent)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		string Line;

		for (const string& Line : vFileContent)
		{
			if (Line != "")
			{
				MyFile << Line << endl;
			}
		}

		MyFile.close();
	}
}

void MoveContent()
{
	vector<string> vFileContent;

	string* FromFile;
	string* ToFile;

	FromFile = new string;
	ToFile = new string;

	*FromFile = GetFileName("\nPlease Enter the File Name and Extension To Convert Content From : ");
	*ToFile = GetFileName("\nPlease Enter the File Name to Move Content To : ");

	LoadDataFromFileToVector(*FromFile, vFileContent);
	SaveVectorToFile(*ToFile, vFileContent);

	cout << "\n______________________Content Converted Successfully______________________\n";

	delete FromFile;
	delete ToFile;
}

void UpdateRecordInFile()
{
	string* FileName;
	string* Record;
	string* UpdateTo;

	FileName = new string;
	Record = new string;
	UpdateTo = new string;

	*FileName = GetFileName("\nPlease Enter the File Name and Extension   : ");
	cin.ignore();

	*Record = GetRecord("\nPlease Enter the Record You Want to Update : ");
	*UpdateTo = GetRecord("\nPlease Enter the New Record to Add         : ");

	vector<string> vFileContent;
	
	LoadDataFromFileToVector(*FileName, vFileContent);

	for (string& Line : vFileContent)
	{
		if (Line == *Record)
		{
			Line = *UpdateTo;
		}
	}
	
	SaveVectorToFile(*FileName, vFileContent);

	cout << "\n_________________Record Updated Successfully_________________\n";

	delete FileName;
	delete Record;
	delete UpdateTo;
}

void DeleteRecordFromFile()
{
	string* FileName;
	string* Record;

	FileName = new string;
	Record = new string;

	vector<string> vFileContent;

	*FileName = GetFileName("\nPlease Enter File Name and Extension : ");
	cin.ignore();

	*Record = GetRecord("\nPlease Enter the Record You Want to Delete : ");

	LoadDataFromFileToVector(*FileName, vFileContent);

	for (string& Line : vFileContent)
	{
		
		if (Line == *Record)
		{
			Line = "";
		}
		
	}

	SaveVectorToFile(*FileName, vFileContent);

	cout << "\n_________________Record Deleted Successfully_________________\n";

	delete FileName;
	delete Record;
}

void RunTask(short TaskNumber)
{
	switch (TaskNumber)
	{

	case 1 :
		CreateFiles();
		break;

	case 2 :
		CheckPrintingContent();
		break;

	case 3 :
		MoveContent();
		break;

	case 4 :
		UpdateRecordInFile();
		break;

	case 5 :
		DeleteRecordFromFile();
		break;

	case 6 :
		CheckWriting();
		break;

	}
}

void StartFileManager()
{
	char* DoTask;
	DoTask = new char;

	*DoTask = 'Y';

	while (*DoTask == 'Y' || *DoTask == 'y')
	{
		ResetScreen();

		cout << "_______________________[Choose a Task]_______________________\n";
		cout << "\n[1]: CreateFiles";
		cout << "\n[2]: Print File Content";
		cout << "\n[3]: Move Content From File To Another File";
		cout << "\n[4]: Update Record";
		cout << "\n[5]: Delete Record";
		cout << "\n[6]: Write Into File";
		cout << "\n_____________________________________________________________\n";

		RunTask(GetTaskNumber());

		cout << "\nDo You Want to Do Another Task? Y/N? ";
		cin >> *DoTask;
	}

	delete DoTask;
}

int main()
{
	
	StartFileManager();

	return 0;
}