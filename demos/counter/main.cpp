#include <QAviWriter.h>

#include <QApplication>
#include <QPainter>
#include <QPixmap>
#include <QSize>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QFont font = app.font();
	font.setPointSize(96);
	font.setBold(true);

	QSize size = QSize(400, 200);
	QRect rect = QRect(QPoint(0, 0), size);

	QAviWriter writer("demo.avi", size);
	writer.open();

	for (int i = 0; i < 100; i++){
		QPixmap pix = QPixmap(size);
		pix.fill(QColor(Qt::white));

		QPainter painter;
		painter.begin(&pix);
		painter.setFont(font);
		painter.drawText(rect, Qt::AlignCenter, QString::number(i + 1));
		painter.end();

		writer.addFrame(pix);
	}

	if (writer.close())
		printf("Succesfully created AVI file with %d frames and %d fps. Encoded using '%s' codec.\n",
		writer.count(), writer.framerate(), writer.codec().toLatin1().constData());

	return app.exec();
}
