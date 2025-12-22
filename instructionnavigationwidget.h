
// instructionnavigationwidget.h
#ifndef INSTRUCTIONNAVIGATIONWIDGET_H
#define INSTRUCTIONNAVIGATIONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QList>

class InstructionNavigationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InstructionNavigationWidget(QWidget *parent = nullptr);

    // Définir la liste des instructions
    void setInstructions(const QStringList &instructions);

    // Obtenir l'index actuel
    int currentIndex() const { return m_currentIndex; }

    // Aller à une instruction spécifique
    void goToInstruction(int index);

signals:
    void instructionChanged(int index, const QString &text);

private slots:
    void onPreviousClicked();
    void onNextClicked();

private:
    void updateDisplay();
    void updateButtons();

    QLabel *m_counterLabel;      // "2/5"
    QLabel *m_instructionLabel;  // Texte de l'instruction
    QPushButton *m_prevButton;
    QPushButton *m_nextButton;

    QStringList m_instructions;
    int m_currentIndex;
};

#endif // INSTRUCTIONNAVIGATIONWIDGET_H
