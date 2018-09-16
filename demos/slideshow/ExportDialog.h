/***************************************************************************
File                 : ExportDialog.h
Project              : libqtavi
--------------------------------------------------------------------
Copyright            : (C) 2017 by Ion Vasilief
Email (use @ for *)  : ion_vasilief*yahoo.fr
Description          : Export AVI options dialog
***************************************************************************/
#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>

class QPushButton;
class QLineEdit;
class QProgressBar;
class QSpinBox;

//! Export AVI options dialog
class ExportDialog : public QDialog
{
	Q_OBJECT

public:
	//! Constructor
	/**
	 * \param parent parent widget
	 */
	ExportDialog(QWidget* parent = 0);

private:
	void enableButtons();
	QLineEdit *aviPathLine;
	QLineEdit *audioPathLine;
	QLineEdit *picturePathLine;
	QPushButton *aviBtn;
	QPushButton *audioBtn;
	QPushButton *picBtn;
	QPushButton *okBtn;
	QPushButton *closeBtn;
	QPushButton *cancelBtn;
	QProgressBar *progressBar;
	QSpinBox *fpsBox;
	QSpinBox *widthBox;

protected slots:
	//! Accept changes
	void accept();
	//! Reject
	void quit();

	void pickAviFile();
	void pickAudioFile();
	void pickPicturesPath();
};

#endif // ExportDialog_H
