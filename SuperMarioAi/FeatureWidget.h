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
		QPalette palette(Qt::GlobalColor::blue);
		QPalette palette2(Qt::GlobalColor::gray);
		featureName = new QLabel();
		featureValue = new QLabel();
		featureName->setAlignment(Qt::AlignLeft);
		featureValue->setAlignment(Qt::AlignCenter);
		hb->addWidget(featureName);
		hb->addWidget(featureValue);
		featureName->setPalette(palette2);
		featureValue->setPalette(palette);
		featureValue->setFixedWidth(100);
		featureName->setFixedWidth(100);
		featureName->setAutoFillBackground(true);
		featureValue->setAutoFillBackground(true);
		setAutoFillBackground(true);
		setPalette(palette);
		show();
	}
	void setFeatureName(std::string name) {
		featureName->setText(QString::fromStdString(name));
	}
	void setFeatureValue(int value) {
		featureValue->setText(QString::number(value));
	}

};

