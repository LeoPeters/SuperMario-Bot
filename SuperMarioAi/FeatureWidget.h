#pragma once
#include <QtWidgets>

class FeatureWidget:public QWidget
{
private:
	QHBoxLayout* hb;
	QLabel* featureName;
	QLabel* featureValue;
public:

	FeatureWidget() {
		hb = new QHBoxLayout(this);
		QPalette palette(Qt::GlobalColor::white);
		featureName = new QLabel();
		featureValue = new QLabel();
		featureName->setAlignment(Qt::AlignLeft);
		featureValue->setAlignment(Qt::AlignCenter);
		hb->addWidget(featureName);
		hb->addWidget(featureValue);
		featureValue->setPalette(palette);
		featureValue->setFixedWidth(200);
		featureName->setFixedWidth(200);
		featureName->setAutoFillBackground(true);
		featureValue->setAutoFillBackground(true);

	}
	void setFeatureName(std::string name) {
		featureName->setText(QString::fromStdString(name));
	}
	void setFeatureValue(int value) {
		featureValue->setText(QString::number(value));
	}

};

