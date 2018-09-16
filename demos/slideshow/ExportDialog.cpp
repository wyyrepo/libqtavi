/***************************************************************************
File                 : ExportDialog.cpp
Project              : libqtavi
--------------------------------------------------------------------
Copyright            : (C) 2017 by Ion Vasilief
Email (use @ for *)  : ion_vasilief*yahoo.fr
Description          : Export AVI options dialog
***************************************************************************/
#include "ExportDialog.h"

#include <QAviWriter.h>

#include <QCoreApplication>
#include <QCompleter>
#include <QDirModel>
#include <QFileDialog>
#include <QGroupBox>
#include <QImageReader>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QProgressBar>
#include <QPushButton>
#include <QSize>
#include <QSpinBox>

ExportDialog::ExportDialog(QWidget *parent)
: QDialog(parent)
{
	setWindowTitle(tr("libqtavi - Slideshow Demo"));
	setSizeGripEnabled(true);
	setWindowIcon(QIcon(":/camera_64.png"));

	QCompleter *completer = new QCompleter(this);
	completer->setModel(new QDirModel(completer));
	completer->setModelSorting(QCompleter::CaseSensitivelySortedModel);
	completer->setCompletionMode(QCompleter::InlineCompletion);

	QGridLayout *gl = new QGridLayout();
	gl->setMargin(2);
	gl->setSpacing(5);

	gl->addWidget(new QLabel(tr("Save as")), 0, 0);

	aviPathLine = new QLineEdit();
	aviPathLine->setCompleter(completer);
	gl->addWidget(aviPathLine, 0, 1);

	aviBtn = new QPushButton(QIcon(":/folder_open.png"), "");
	aviBtn->setToolTip(tr("Browse"));
	connect(aviBtn, SIGNAL(clicked()), this, SLOT(pickAviFile()));
	gl->addWidget(aviBtn, 0, 2);

	gl->addWidget(new QLabel(tr("Audio track")), 1, 0);

	audioPathLine = new QLineEdit();
	audioPathLine->setCompleter(completer);
	gl->addWidget(audioPathLine, 1, 1);

	audioBtn = new QPushButton(QIcon(":/folder_open.png"), "");
	audioBtn->setToolTip(tr("Browse"));
	connect(audioBtn, SIGNAL(clicked()), this, SLOT(pickAudioFile()));
	gl->addWidget(audioBtn, 1, 2);

	gl->addWidget(new QLabel(tr("Pictures")), 2, 0);

	picturePathLine = new QLineEdit();
	picturePathLine->setText(QDir::toNativeSeparators(QDir::homePath()));
	picturePathLine->setCompleter(completer);
	gl->addWidget(picturePathLine, 2, 1);

	picBtn = new QPushButton(QIcon(":/folder_open.png"), "");
	picBtn->setToolTip(tr("Browse"));
	connect(picBtn, SIGNAL(clicked()), this, SLOT(pickPicturesPath()));
	gl->addWidget(picBtn, 2, 2);

	gl->addWidget(new QLabel(tr("Framerate")), 3, 0);

	fpsBox = new QSpinBox;
	fpsBox->setMinimum(1);
	fpsBox->setValue(1);
	fpsBox->setSuffix(" " + tr("fps"));
	gl->addWidget(fpsBox, 3, 1);

	gl->addWidget(new QLabel(tr("Width")), 4, 0);

	widthBox = new QSpinBox;
	widthBox->setRange(2, 10000);
	widthBox->setValue(800);
	widthBox->setSuffix(" " + tr("pixels"));
	gl->addWidget(widthBox, 4, 1);

	gl->setColumnStretch(1, 10);
	gl->setRowStretch(5, 1);

	progressBar = new QProgressBar;
	progressBar->setEnabled(false);

	QVBoxLayout *vl1 = new QVBoxLayout;
	vl1->addLayout(gl);
	vl1->addWidget(progressBar);
	vl1->setMargin(0);
	vl1->setSpacing(0);

	QVBoxLayout *vl2 = new QVBoxLayout;
	vl2->setMargin(0);
	vl2->setSpacing(5);

	okBtn = new QPushButton(QIcon(":/run.png"), "");
	okBtn->setDefault(true);
	okBtn->setAutoDefault(false);
	connect(okBtn, SIGNAL(clicked()), this, SLOT(accept()));
	vl2->addWidget(okBtn);

	closeBtn = new QPushButton(QIcon(":/exit.png"), "");
	closeBtn->setAutoDefault(false);
	connect(closeBtn, SIGNAL(clicked()), this, SLOT(quit()));
	vl2->addWidget(closeBtn);
	vl2->addStretch();

	cancelBtn = new QPushButton(QIcon(":/pause.png"), "");
	cancelBtn->setCheckable(true);
	cancelBtn->setAutoDefault(false);
	cancelBtn->setEnabled(false);
	vl2->addWidget(cancelBtn);

	QHBoxLayout *hl = new QHBoxLayout(this);
	hl->addLayout(vl1);
	hl->addLayout(vl2);
	hl->setMargin(5);
	hl->setSpacing(2);

#ifdef Q_OS_ANDROID
	QFont fnt = font();
	fnt.setPointSize(fnt.pointSize() - 14);
	setFont(fnt);
	aviPathLine->setText("/sdcard/DCIM/Camera/demo.avi");
	picturePathLine->setText("/sdcard/DCIM/Camera");
#else
	okBtn->setText(tr("&Encode"));
	closeBtn->setText(tr("&Quit"));
	cancelBtn->setText(tr("&Cancel"));
	aviPathLine->setMinimumWidth(300);
	aviPathLine->setText(QDir::toNativeSeparators(QDir::homePath().append("/Desktop/demo.avi")));
#endif
}

void ExportDialog::pickAviFile()
{
	QString path = aviPathLine->text();
	if (path.isEmpty()){
	#ifdef Q_OS_ANDROID
		path = "/sdcard/DCIM/Camera/demo.avi";
	#else
		path = QDir::toNativeSeparators(QDir::homePath().append("/Desktop/demo.avi"));
	#endif
	}

	QString aviFileName = QFileDialog::getSaveFileName(this, tr("Please choose the output path"), path, tr("Video File (*.avi)"));
	if (!aviFileName.isEmpty())
		aviPathLine->setText(QDir::toNativeSeparators(aviFileName));
}

void ExportDialog::pickAudioFile()
{
	QString path = audioPathLine->text();
	if (path.isEmpty())
		path = QDir::homePath();

	QString nameFilters = tr("Audio File").append(" (");
	foreach (QByteArray ba, QAviWriter::supportedAudioFormats()){
		QString filter = QString(ba);
		nameFilters.append(QString("*.").append(filter.toLower()));
		nameFilters.append(" ");
	}
	nameFilters.append(")");

	QString audioFileName = QFileDialog::getOpenFileName(this, tr("Please choose an audio track"), path, nameFilters);
	if (!audioFileName.isEmpty())
		audioPathLine->setText(QDir::toNativeSeparators(audioFileName));
}

void ExportDialog::pickPicturesPath()
{
	QString path = picturePathLine->text();
	if (path.isEmpty()){
	#ifdef Q_OS_ANDROID
		path = "/sdcard/DCIM/Camera";
	#else
		path = QDir::homePath();
	#endif
	}

	path = QFileDialog::getExistingDirectory(this, tr("Please choose the pictures folder!"), path,
	QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!path.isEmpty())
		picturePathLine->setText(QDir::toNativeSeparators(path));
}

void ExportDialog::quit()
{
	exit(0);
}

void ExportDialog::accept()
{
	QString picPath = picturePathLine->text();
	if (picPath.isEmpty()){
		QMessageBox::critical(this, tr("Error"), tr("Please choose the pictures folder!"));
		picturePathLine->setFocus();
		return;
	}

	QStringList nameFilters;
	foreach (QByteArray ba, QImageReader::supportedImageFormats()){
		QString filter = QString(ba);
		nameFilters.append(QString("*.").append(filter.toLower()));
		nameFilters.append(QString("*.").append(filter));
	}

	QDir dir = QDir(picPath);
	QFileInfoList infoList = dir.entryInfoList(nameFilters, QDir::Files | QDir::Readable | QDir::NoDotAndDotDot);
	int count = infoList.count();
	if (!count){
		QMessageBox::critical(this, tr("Error"), tr("Please choose a folder containing valid picture files!"));
		picturePathLine->setFocus();
		return;
	}

	int width = widthBox->value(), maxHeight = 0;
	QSize size = QSize(width, width);
	QAviWriter writer(aviPathLine->text(), size, fpsBox->value());

	QString audioPath = audioPathLine->text();
	if (!audioPath.isEmpty())
		writer.setAudioFileName(audioPath);

	writer.open();

	picBtn->setEnabled(false);
	aviBtn->setEnabled(false);
	audioBtn->setEnabled(false);
	okBtn->setEnabled(false);

	progressBar->setEnabled(true);
	cancelBtn->setEnabled(true);
	cancelBtn->setFocus();

	progressBar->setMaximum(count);
	foreach (QFileInfo fi, infoList){
		QCoreApplication::processEvents();
		if (cancelBtn->isDown()){
			cancelBtn->setDown(false);
			enableButtons();
			break;
		}

		QImage img;
		if (!img.load(picPath + "/" + fi.fileName())){
			progressBar->setMaximum(--count);
			continue;
		}

		img = img.scaled(size, Qt::KeepAspectRatio);
		if (img.width() != width){
			progressBar->setMaximum(--count);
			continue;
		}

		if (img.height() > maxHeight)
			maxHeight = img.height();

		writer.addFrame(img);
		progressBar->setValue(writer.count());
	}

	writer.setSize(QSize(width, maxHeight));

	if (writer.close()){
		QMessageBox::information(this, tr("Success"),
		tr("Created file '%1'\nusing %2 frames and a framerate of %3 fps. Encoded using '%4' codec.")
		.arg(writer.fileName())
		.arg(writer.count())
		.arg(writer.framerate())
		.arg(writer.codec()));
	}

	enableButtons();
}

void ExportDialog::enableButtons()
{
	picBtn->setEnabled(true);
	aviBtn->setEnabled(true);
	audioBtn->setEnabled(true);
	okBtn->setEnabled(true);
	okBtn->setFocus();
	cancelBtn->setEnabled(false);
}
