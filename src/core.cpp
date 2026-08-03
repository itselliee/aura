#include <iostream>

#include <core.hpp>

namespace AuraEngine {
Core::Core() {}
Core::~Core() {}

void Core::Init() { std::cout << "Starting engine job.." << std::endl; }

void Core::Update() {}
} // namespace AuraEngine
