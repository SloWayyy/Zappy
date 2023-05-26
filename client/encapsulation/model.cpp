/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** model
*/

#include "encapsulation/Raylibcpp.hpp"

Raylibcpp::RayModel::RayModel()
{
    std::array<std::pair<modelType, std::pair<std::string, std::string>>, 1> model = {
        {
            {this->PING, {"assets/ia/ia.obj", "assets/ia/textures/ia.png"}},
        }
    };
    for (const auto &i : model) {
        this->_modelArray.push_back(modelLoad(LoadModel(i.second.first.c_str()), i.first, 0, 0, LoadTexture(i.second.second.c_str())));
        SetMaterialTexture(&this->getModelLoad(i.first)._model.materials[0], MATERIAL_MAP_DIFFUSE, this->getTexture(i.first));
    }
}

Raylibcpp::RayModel::modelLoad &Raylibcpp::RayModel::getModelLoad(Raylibcpp::RayModel::modelType type)
{
    for (auto &i : this->_modelArray) {
        if (i._type == type)
            return i;
    }
}

Texture2D Raylibcpp::RayModel::getTexture(Raylibcpp::RayModel::modelType type)
{
    for (auto &i : this->_modelArray) {
        if (i._type == type)
            return i._texture;
    }
}

void Raylibcpp::RayModel::drawRayModel(Raylibcpp::RayModel::modelType type, Vector3 pos, float scale)
{
    modelLoad mod = this->getModelLoad(type);

    DrawModel(mod._model, pos, scale, WHITE);
}

Raylibcpp::RayModel::~RayModel()
{

}
