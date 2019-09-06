#ifndef MATLEDITOR_H
#define MATLEDITOR_H

#include <QDialog>
#include "VGLMaterial.h"

namespace Ui {
class MatlEditor;
}

class MatlEditor : public QDialog
{
    Q_OBJECT

public:
    explicit MatlEditor(QWidget *parent = 0);
    ~MatlEditor();

    VGLMaterial material() const;

private slots:
    void on_buttonOk_clicked();

    void on_buttonCancel_clicked();

    void on_buttonHelp_clicked();

    void on_pushButtonDefault_clicked();

    void on_pushButtonBrass_clicked();

    void on_pushButtonBronze_clicked();

    void on_pushButtonCopper_clicked();

    void on_pushButtonSilver_clicked();

    void on_pushButtonGold_clicked();

    void on_pushButtonJade_clicked();

    void on_pushButtonPerl_clicked();

    void on_pushButtonPlastic_clicked();

    void on_pushButtonRuby_clicked();

    void on_pushButtonTurquoise_clicked();

    void on_sliderMAR_valueChanged(int value);

    void on_sliderMAG_valueChanged(int value);

    void on_sliderMAB_valueChanged(int value);

    void on_sliderMDR_valueChanged(int value);

    void on_sliderMDG_valueChanged(int value);

    void on_sliderMDB_valueChanged(int value);

    void on_sliderMSR_valueChanged(int value);

    void on_sliderMSG_valueChanged(int value);

    void on_sliderMSB_valueChanged(int value);

    void on_sliderShine_valueChanged(int value);

private:
    Ui::MatlEditor *ui;
    VGLMaterial myMaterial;
};

#endif // MATLEDITOR_H
