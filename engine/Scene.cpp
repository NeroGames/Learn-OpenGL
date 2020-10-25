////////////////////////////////////////////////////////////
// Learn OpenGL
// Copyright (c) 2020 sk-landry
////////////////////////////////////////////////////////////
///////////////////////////HEADERS//////////////////////////
#include "Scene.h"
////////////////////////////////////////////////////////////

Scene::Scene()
{
    //ctor
}

Scene::~Scene()
{
    //dtor
}

void Scene::init()
{

}

void Scene::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Scene::render()
{

}

void Scene::destroy()
{

}

void Scene::handleEvent(const sf::Event& event)
{

}

void Scene::setSceneName(const std::string& name)
{
    m_SceneName = name;
}

std::string Scene::getSceneName()
{
    return m_SceneName;
}

sf::Vector2f Scene::getResolution()
{
    return m_Resolution;
}



