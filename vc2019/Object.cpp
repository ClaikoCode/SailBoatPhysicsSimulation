#include "Includes/Object.h"

constexpr bool DEFAULT_STATIC_STATE = false;
constexpr bool DEFAULT_DRAWABLE_STATE = true;

Object::Object()
	: Object(Transform()) {}

Object::Object(const Transform& transform)
	: m_Transform(transform), 
	m_IsStatic(DEFAULT_STATIC_STATE),
	m_IsDrawable(DEFAULT_DRAWABLE_STATE) {}

void Object::EnableStatic() { m_IsStatic = true; }
void Object::DisableStatic() { m_IsStatic = false; }

void Object::EnableDrawable() { m_IsDrawable = true; }
void Object::DisableDrawable() { m_IsDrawable = false; }
