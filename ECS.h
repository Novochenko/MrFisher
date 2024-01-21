#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;



using ComponentID = std::size_t;
using Group = std::size_t;
inline ComponentID getComponentID() { // т.н список id, для всех общий, т.к статический, объявляется 1 раз, остальные 
	static ComponentID lastID = 0u;// просто инкрементируется
	return lastID++;
}
template <class T>
inline ComponentID getComponentTypeID() noexcept{
	static ComponentID typeID = getComponentID();// для каждого типа шаблона своя статическая переменная, следовательно
	return typeID;// нешаблонная функция для шаблонной будет вызываться единожды, остальные разы просто возвращать id
}
constexpr ComponentID maxComponents = 32;
constexpr std::size_t maxGroups = 32;
using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;
class Component {
public:
	Entity* entity;

	virtual void Draw(){}
	virtual void Update(){}
	virtual void Init(){}

	virtual ~Component(){}
	bool freeze = false;
	bool isActive = true;
};

static size_t EntityNum = 0;

class Entity {
private:
	bool active = true;
	std::vector <std::unique_ptr<Component>> components;
	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;
	
public:
	const char* name;
	Manager& manager;
 	Entity(Manager& mManager) : manager(mManager){	
	}
	
	void Update() {
		for (auto& c : components) {
			c->Update();
		}
	}
	void Draw() {
		for (auto& c : components) {
			if (c != nullptr)
				c->Draw();
		}
	}
	/*void Draw() {
		for (std::vector<std::unique_ptr<Component>>::iterator i = components.begin(); i != components.end(); ++i) {
			std::unique_ptr<Component>& c = *i;
			c->Draw();
		}
	}*/
	void destroy()
	{
		//active = false;
		for (auto& c : componentArray) {
			//c->isActive = false;
			c = nullptr;
			
		}
		for (size_t c = 0; c < maxComponents; c++) {
			//c->isActive = false;
			componentBitSet[c] = false;

		}
		components.clear();
		

	}
	/*void Update() {
		for (std::vector<std::unique_ptr<Component>>::iterator i = components.begin(), int c = 0; i != components.end(); ++i; c++) {
			components[c]->Update();
		}
	}
	void Draw() {
		for (std::vector<std::unique_ptr<Component>>::iterator i = components.begin(), int c = 0; i != components.end(); ++i, c++) {
			components[c]->Draw();
		}
	}*/
	bool IsActive() const { return active; }
	//void Destroy() { 
	//	/*active = false;*/ 
	//	for (auto &c : components) {
	//		c->isActive = false;
	//	}
	//}
	bool hasGroup(Group mGroup) {
		return groupBitSet[mGroup];
	}
	void addGroup(Group mGroup);
	void deleteGroup(Group mGroup) {
		groupBitSet[mGroup] = false;
	}
	template <typename T>
	bool HasComponent() const {
		return componentBitSet[getComponentTypeID<T>()];
	}
	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {
		T* c = new T(std::forward<TArgs>(mArgs)...);
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		
		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;
		c->Init();
		return *c;
	}
	template <typename T>
	T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
	void FreezeEntity(){
		for (auto& c : components){
			c->freeze = true;
		}
	}
	void UnFreezeEntity(){
		for (auto& c : components){
			c->freeze = false;
		}
	}
	void Hold(){
		for (auto& c : components){
			c->isActive = false;
		}
	}
	void unHold(){
		for (auto& c : components){
			c->isActive = true;
		}
	}

};
//constexpr std::size_t maxEntity = 32;
//using EntitiesBitSet = std::bitset<maxEntity>;
class Manager {
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::vector<std::size_t> entitiesNames;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;
public:
	
	void Update() {
		for (auto& e : entities) e->Update();
	}
	void Draw() {
		for (auto& e : entities) e->Draw();
	}
	void destroy()
	{
		for (auto& e : entities)
		{
			e->destroy();
		}
		for (size_t i = 0; i < maxGroups; i++) {
			groupedEntities[i].clear();
		}
	}
	void Refresh() {
		for (unsigned i = 0u; i < maxGroups; i++) {
			std::vector<Entity*> &v = groupedEntities[i];
			v.erase(
				std::remove_if(v.begin(), v.end(),
				[i](Entity* mEntity) {
					return !mEntity->IsActive() || !mEntity->hasGroup(i);
				}), 
				v.end());
			
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity) {
				return !(mEntity->IsActive());
			}), std::end(entities));
	}
	void AddtoGroup(Entity* mEntity, Group mGroup) {
		groupedEntities[mGroup].emplace_back(mEntity);
	}
	std::vector<Entity*>& getGroup(Group mGroup) {
		return groupedEntities[mGroup];
	}
	Entity& addEntity() {
		/*Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr { e };*/

		std::unique_ptr<Entity> uPtr = std::unique_ptr<Entity>(new Entity(*this));
		Entity *e = uPtr.get();
		entities.push_back(std::move(uPtr));
		//entitiesNames.push_back(name);
		return *e;
	}


};