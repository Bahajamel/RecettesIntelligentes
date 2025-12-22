#include "ControllerHeader/ImageDropLabel.h"

#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QFileInfo>
#include <QUrl>

ImageDropLabel::ImageDropLabel(QWidget *parent)
    : QLabel(parent)
{
    setAcceptDrops(true);
    setAlignment(Qt::AlignCenter);
    setMinimumHeight(250);
    setMaximumHeight(350);
    setScaledContents(false);

    applyNormalStyle();
}

void ImageDropLabel::applyNormalStyle()
{
    setStyleSheet(
        "QLabel { "
        "  background: rgba(245, 242, 232, 0.3); "
        "  border: 2px dashed #e5ddd0; "
        "  border-radius: 12px; "
        "  color: #6b7280; "
        "  font-size: 14px; "
        "} "
        "QLabel:hover { "
        "  border-color: #d97706; "
        "  background: rgba(217, 119, 6, 0.05); "
        "}"
        );
}

void ImageDropLabel::applyHoverStyle()
{
    setStyleSheet(
        "QLabel { "
        "  background: rgba(217, 119, 6, 0.1); "
        "  border: 2px solid #d97706; "
        "  border-radius: 12px; "
        "}"
        );
}

void ImageDropLabel::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls() || event->mimeData()->hasImage()) {
        event->acceptProposedAction();
        applyHoverStyle();
    }
}

void ImageDropLabel::dragLeaveEvent(QDragLeaveEvent *event)
{
    Q_UNUSED(event);
    applyNormalStyle();
}

void ImageDropLabel::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();

    if (mimeData->hasUrls()) {
        const QList<QUrl> urls = mimeData->urls();
        if (!urls.isEmpty()) {
            const QString filePath = urls.first().toLocalFile();
            if (!filePath.isEmpty()) {
                const QStringList imageFormats = {
                    "png", "jpg", "jpeg", "gif", "bmp", "webp"
                };

                const QString ext = QFileInfo(filePath).suffix().toLower();
                if (imageFormats.contains(ext)) {
                    emit imageDropped(filePath);
                    event->acceptProposedAction();
                }
            }
        }
    }

    applyNormalStyle();
}
