// instructionnavigationwidget.cpp
#include "instructionnavigationwidget.h"
#include <QFont>

InstructionNavigationWidget::InstructionNavigationWidget(QWidget *parent)
    : QWidget(parent)
    , m_currentIndex(0)
{
    // Layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Compteur (ex: "2/5")
    m_counterLabel = new QLabel("0/0", this);
    m_counterLabel->setAlignment(Qt::AlignCenter);
    QFont counterFont = m_counterLabel->font();
    counterFont.setPointSize(14);
    counterFont.setBold(true);
    m_counterLabel->setFont(counterFont);
    m_counterLabel->setStyleSheet("color: #D97706;");

    // Label de l'instruction
    m_instructionLabel = new QLabel("Aucune instruction", this);
    m_instructionLabel->setWordWrap(true);
    m_instructionLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_instructionLabel->setMinimumHeight(100);
    QFont instructionFont = m_instructionLabel->font();
    instructionFont.setPointSize(16);
    m_instructionLabel->setFont(instructionFont);
    m_instructionLabel->setStyleSheet(
        "background-color: #FEF3C7; "
        "border: 2px solid #FCD34D; "
        "border-radius: 10px; "
        "padding: 20px;"
        );

    // Boutons de navigation
    QHBoxLayout *navLayout = new QHBoxLayout();
    navLayout->setSpacing(10);

    m_prevButton = new QPushButton("← Précédent", this);
    m_nextButton = new QPushButton("Suivant →", this);

    // Style des boutons
    QString buttonStyle =
        "QPushButton {"
        "   background-color: #D97706;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   padding: 12px 24px;"
        "   font-size: 14px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #B45309;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #92400E;"
        "}"
        "QPushButton:disabled {"
        "   background-color: #D1D5DB;"
        "   color: #9CA3AF;"
        "}";

    m_prevButton->setStyleSheet(buttonStyle);
    m_nextButton->setStyleSheet(buttonStyle);
    m_prevButton->setCursor(Qt::PointingHandCursor);
    m_nextButton->setCursor(Qt::PointingHandCursor);

    navLayout->addWidget(m_prevButton);
    navLayout->addStretch();
    navLayout->addWidget(m_nextButton);

    // Assemblage
    mainLayout->addWidget(m_counterLabel);
    mainLayout->addWidget(m_instructionLabel);
    mainLayout->addLayout(navLayout);

    // Connexions
    connect(m_prevButton, &QPushButton::clicked, this, &InstructionNavigationWidget::onPreviousClicked);
    connect(m_nextButton, &QPushButton::clicked, this, &InstructionNavigationWidget::onNextClicked);

    updateButtons();
}

void InstructionNavigationWidget::setInstructions(const QStringList &instructions)
{
    m_instructions = instructions;
    m_currentIndex = 0;
    updateDisplay();
    updateButtons();
}

void InstructionNavigationWidget::goToInstruction(int index)
{
    if (index >= 0 && index < m_instructions.size()) {
        m_currentIndex = index;
        updateDisplay();
        updateButtons();
    }
}

void InstructionNavigationWidget::onPreviousClicked()
{
    if (m_currentIndex > 0) {
        m_currentIndex--;
        updateDisplay();
        updateButtons();
        emit instructionChanged(m_currentIndex, m_instructions[m_currentIndex]);
    }
}

void InstructionNavigationWidget::onNextClicked()
{
    if (m_currentIndex < m_instructions.size() - 1) {
        m_currentIndex++;
        updateDisplay();
        updateButtons();
        emit instructionChanged(m_currentIndex, m_instructions[m_currentIndex]);
    }
}

void InstructionNavigationWidget::updateDisplay()
{
    if (m_instructions.isEmpty()) {
        m_counterLabel->setText("0/0");
        m_instructionLabel->setText("Aucune instruction disponible");
        return;
    }

    // Mise à jour du compteur
    m_counterLabel->setText(QString("%1/%2")
                                .arg(m_currentIndex + 1)
                                .arg(m_instructions.size()));

    // Mise à jour de l'instruction
    QString instruction = m_instructions[m_currentIndex];
    m_instructionLabel->setText(QString("<b>%1.</b> %2")
                                    .arg(m_currentIndex + 1)
                                    .arg(instruction));
}

void InstructionNavigationWidget::updateButtons()
{
    m_prevButton->setEnabled(m_currentIndex > 0);
    m_nextButton->setEnabled(m_currentIndex < m_instructions.size() - 1);
}


