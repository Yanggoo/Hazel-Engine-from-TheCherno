#pragma once

//for use by Hazel applications
#include "Hazel/Core/Application.h"
#include "Hazel/Core/Layer.h"
#include "Hazel/Core/Log.h"
#include "Hazel/Core/Base.h"
#include "Hazel/ImGui/ImGuiLayer.h"
#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Core/MouseCodes.h"
#include "Hazel/Core/Input.h"
#include "Hazel/Core/Assert.h"


//---Render---------------------- 
#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Renderer/GraphicContext.h"
#include "Hazel/Renderer/OrthographicCamera.h"
#include "Hazel/Renderer/RenderCommand.h"
#include "Hazel/Renderer/Renderer.h"
#include "Hazel/Renderer/Renderer2D.h"
#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/VertexArray.h"
#include "Hazel/Renderer/Texture.h"
#include "Hazel/Renderer/Framebuffer.h"
//---Render---------------------- 

//---Scene----------------------- 
#include "Hazel/Scene/Scene.h"
#include "Hazel/Scene/Components.h"
#include "Hazel/Scene/Entity.h"
#include "Hazel/Scene/ScriptableEntity.h"
//---Scene----------------------- 

//---Panel----------------------- 
#include "Hazel/Panels/SceneHierarchyPanel.h"
//---Panel-----------------------