#include "QValueTable.h"
#include <QHeaderView>
#include <QSizePolicy>
#include <iostream>
#include <qstringlistmodel.h>
#include "Globals.h"

QValueTable::QValueTable()
{
	model = new QStandardItemModel(NUMBER_OF_STATES, 10, this);

	this->setModel(model);
	QValueHeaderList.append("Q-Value: Move Right");
	QValueHeaderList.append("Q-Value: Jump");
	QValueHeaderList.append("Q-Value: High Jump");
	QValueHeaderList.append("Q-Value: Move Left");
	QValueHeaderList.append("Q-Value: Shoot");
	FeatureHeaderList.append("Feature: Under Block");
	FeatureHeaderList.append("Feature: Enemy X");
	FeatureHeaderList.append("Feature: Enemy Y");
	FeatureHeaderList.append("Feature: Obstacle Right");
	headerList.append("State");
	headerList.append(QValueHeaderList);
	headerList.append(FeatureHeaderList);
	model->setHorizontalHeaderLabels(headerList);
	//setHorizontalHeaderLabels(headerList);
	resizeColumnsToContents();
	verticalHeader()->hide();

	for (int i = 0; i < model->rowCount(); i++) {

		QModelIndex index = model->index(i, 0, QModelIndex());
		model->setData(index, i);
	}
}

void QValueTable::setQVlaues(std::vector<std::vector<double>> qValues)
{
	this->qValues = qValues;
}

void QValueTable::setFeatureValues(std::vector<std::vector<int>> featureValues)
{
	this->featureValues = featureValues;
}

void QValueTable::updateWholeTable()
{
	for (int i = 0; i < qValues.size(); i++) {
		for (int j = 0; j < qValues.at(i).size(); j++) {
			QModelIndex index = model->index(i, j+1, QModelIndex());
			model->setData(index, qValues.at(i).at(j));
		}
	}
}

void QValueTable::updateTable(int row, std::vector<double> rowValue)
{

	for (int j = 0; j < rowValue.size(); j++) {
		QModelIndex index = model->index(row, j + 1, QModelIndex());
		model->setData(index, rowValue.at(j));

		//std::cout << "Size: "<< rowValue.size() << std::endl;

	}

}
