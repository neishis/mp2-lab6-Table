#pragma once
#include "ArrayHashTable.h"
#include "ListHashTable.h"
#include "ScanTable.h"
#include "SortTable.h"

#include <string>
#include <iostream>

using namespace std;

void testTable(Table<int, string>& table, const string& name) {
	cout << "Testing " << name << "\n";

		table.Insert({ 1, "one" });
		table.Insert({ 2, "two" });
		table.Insert({ 3, "three" });
		cout << "Insert OK\n";
		cout << "Efficiency: " << table.getEff() << endl;
	

	cout << "Find key 2: " << (table.Find(2) ? "Found" : "Not found") << endl;
	cout << "Efficiency: " << table.getEff() << endl;

	cout << "Find key 4: " << (table.Find(4) ? "Found" : "Not found") << endl;
	cout << "Efficiency: " << table.getEff() << endl;

	table.Delete(2);
	cout << "Efficiency: " << table.getEff() << endl;

	cout << "Find key 2 after delete: " << (table.Find(2) ? "Found" : "Not found") << endl;

	cout << "Table content:" << endl << table << endl;
	cout << "Efficiency: " << table.getEff() << endl;
	cout << endl;
}



int main() {
	ScanTable<int, std::string> scanTable(10);
	SortTable<int, std::string> sortTable(10);
	ArrayHashTable<int, std::string> arrayHashTable(10, 3);
	ListHashTable<int, std::string> listHashTable(10);

	testTable(scanTable, "ScanTable");
	testTable(sortTable, "SortTable");
	testTable(arrayHashTable, "ArrayHashTable");
	testTable(listHashTable, "ListHashTable");
}