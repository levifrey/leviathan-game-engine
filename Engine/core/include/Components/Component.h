#pragma once
class GameObject;
class Component {
    public:
        Component() {}
        Component(GameObject* game_object) : game_object_(game_object) {}
        virtual ~Component() = default;
        virtual void update() {}
        virtual void init() {}
        void setGameObject(GameObject* obj) { game_object_ = obj; }
        GameObject* getGameObject() const { return game_object_; }
        
    private:
        GameObject* game_object_;
};
