#include "MatlEditor.h"
#include "ui_MatlEditor.h"

MatlEditor::MatlEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MatlEditor)
{
    ui->setupUi(this);
}

MatlEditor::~MatlEditor()
{
    delete ui;
}

VGLMaterial MatlEditor::material() const
{
    return myMaterial;
}

void MatlEditor::on_buttonOk_clicked()
{
    close();
}

void MatlEditor::on_buttonCancel_clicked()
{
    close();
}

void MatlEditor::on_buttonHelp_clicked()
{

}

void MatlEditor::on_pushButtonDefault_clicked()
{
    myMaterial.SetName(DEFAULT);
}

void MatlEditor::on_pushButtonBrass_clicked()
{
    myMaterial.SetName(BRASS);
}

void MatlEditor::on_pushButtonBronze_clicked()
{
    myMaterial.SetName(BRONZE);
}

void MatlEditor::on_pushButtonCopper_clicked()
{
    myMaterial.SetName(COPPER);
}

void MatlEditor::on_pushButtonSilver_clicked()
{
    myMaterial.SetName(SILVER);
}

void MatlEditor::on_pushButtonGold_clicked()
{
    myMaterial.SetName(GOLD);
}

void MatlEditor::on_pushButtonJade_clicked()
{
    myMaterial.SetName(JADE);
}

void MatlEditor::on_pushButtonPerl_clicked()
{
    myMaterial.SetName(PEARL);
}

void MatlEditor::on_pushButtonPlastic_clicked()
{
    myMaterial.SetName(PLASTIC);
}

void MatlEditor::on_pushButtonRuby_clicked()
{
    myMaterial.SetName(RUBY);
}

void MatlEditor::on_pushButtonTurquoise_clicked()
{
    myMaterial.SetName(TURQUOISE);
}

void MatlEditor::on_sliderMAR_valueChanged(int value)
{
    VGLColor color = myMaterial.GetAmbient();
    color.SetRed(static_cast<float>(256)/static_cast<float>(value));
    myMaterial.SetAmbient(color);
}

void MatlEditor::on_sliderMAG_valueChanged(int value)
{
    VGLColor color = myMaterial.GetAmbient();
    color.SetGreen(static_cast<float>(256)/static_cast<float>(value));
    myMaterial.SetAmbient(color);
}

void MatlEditor::on_sliderMAB_valueChanged(int value)
{
    VGLColor color = myMaterial.GetAmbient();
    color.SetBlue(static_cast<float>(256)/static_cast<float>(value));
    myMaterial.SetAmbient(color);
}

void MatlEditor::on_sliderMDR_valueChanged(int value)
{
    VGLColor color = myMaterial.GetDiffuse();
    color.SetRed(static_cast<float>(256)/static_cast<float>(value));
    myMaterial.SetDiffuse(color);
}

void MatlEditor::on_sliderMDG_valueChanged(int value)
{
    VGLColor color = myMaterial.GetDiffuse();
    color.SetGreen(static_cast<float>(256)/static_cast<float>(value));
    myMaterial.SetDiffuse(color);
}

void MatlEditor::on_sliderMDB_valueChanged(int value)
{
    VGLColor color = myMaterial.GetDiffuse();
    color.SetBlue(static_cast<float>(256)/static_cast<float>(value));
    myMaterial.SetDiffuse(color);
}

void MatlEditor::on_sliderMSR_valueChanged(int value)
{
    VGLColor color = myMaterial.GetSpecular();
    color.SetRed(static_cast<float>(256)/static_cast<float>(value));
    myMaterial.SetSpecular(color);
}

void MatlEditor::on_sliderMSG_valueChanged(int value)
{
    VGLColor color = myMaterial.GetSpecular();
    color.SetGreen(static_cast<float>(256)/static_cast<float>(value));
    myMaterial.SetSpecular(color);
}

void MatlEditor::on_sliderMSB_valueChanged(int value)
{
    VGLColor color = myMaterial.GetSpecular();
    color.SetBlue(static_cast<float>(256)/static_cast<float>(value));
    myMaterial.SetSpecular(color);
}

void MatlEditor::on_sliderShine_valueChanged(int value)
{
    myMaterial.SetShininessCoeff(static_cast<float>(256)/static_cast<float>(value));
}
