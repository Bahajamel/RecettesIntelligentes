#ifndef IMAGEDROPLABEL_H
#define IMAGEDROPLABEL_H

#include <QLabel>
#include <QString>

class ImageDropLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ImageDropLabel(QWidget *parent = nullptr);

signals:
    void imageDropped(const QString &filePath);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    void applyNormalStyle();
    void applyHoverStyle();
};

#endif // IMAGEDROPLABEL_H
