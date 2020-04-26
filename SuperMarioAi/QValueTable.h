#pragma once
#include <QtableWidget>
#include <QStandardItemModel>

class QValueTable :public QTableView{
public:
	QValueTable();
	void setQVlaues(std::vector<std::vector<double>> qValues);
	void setFeatureValues(std::vector<std::vector<int>> featureValues);
	void updateWholeTable();
	void updateTable(int, std::vector<double> rowValue);
private:
	QStandardItemModel* model;
	QStringList QValueHeaderList;
	QStringList FeatureHeaderList;
	QStringList headerList;
	std::vector<std::vector<double>> qValues;
	std::vector<std::vector<int>> featureValues;


};