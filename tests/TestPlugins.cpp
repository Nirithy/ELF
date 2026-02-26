#include "TestFramework.h"
#include "elfparser/plugins/core/PluginManager.h"
#include "elfparser/plugins/core/IPlugin.h"
#include "elfparser/plugins/core/PluginInfo.h"
#include "elfparser/common/Types.h"
#include <iostream>

using namespace ElfParser::Plugins;

class MockPlugin : public IPlugin {
public:
    MockPlugin() {
        m_info.name = "MockPlugin";
        m_info.version = "1.0.0";
    }

    const PluginInfo& GetInfo() const override {
        return m_info;
    }

    ElfParser::Common::Result Initialize(PluginContext& context) override {
        m_initialized = true;
        return ElfParser::Common::Result::Ok();
    }

    ElfParser::Common::Result Shutdown() override {
        m_initialized = false;
        return ElfParser::Common::Result::Ok();
    }

    bool IsInitialized() const { return m_initialized; }

private:
    PluginInfo m_info;
    bool m_initialized = false;
};

TEST_CASE(TestPluginLifecycle) {
    PluginManager manager;
    ASSERT_TRUE(manager.Initialize().IsOk());

    auto plugin = std::make_unique<MockPlugin>();
    MockPlugin* pluginRef = plugin.get();

    ASSERT_TRUE(manager.RegisterPlugin(std::move(plugin)).IsOk());
    ASSERT_TRUE(manager.InitializePlugins().IsOk());

    ASSERT_TRUE(pluginRef->IsInitialized());

    ASSERT_TRUE(manager.ShutdownPlugins().IsOk());
}

TEST_CASE(TestPluginEvent) {
    PluginManager manager;
    ASSERT_TRUE(manager.Initialize().IsOk());

    bool eventReceived = false;

    // Register a listener manually to the dispatcher
    class TestListener : public ElfParser::Plugins::Events::IEventListener {
    public:
        TestListener(bool& flag) : m_flag(flag) {}
        void OnEvent(const ElfParser::Plugins::Events::Event& event) override {
            if (event.GetType() == ElfParser::Plugins::Events::EventType::PluginLoaded) {
                m_flag = true;
            }
        }
    private:
        bool& m_flag;
    };

    auto listener = std::make_shared<TestListener>(eventReceived);
    manager.GetEventDispatcher()->RegisterListener(listener);

    auto plugin = std::make_unique<MockPlugin>();
    ASSERT_TRUE(manager.RegisterPlugin(std::move(plugin)).IsOk());
    ASSERT_TRUE(manager.InitializePlugins().IsOk());

    ASSERT_TRUE(eventReceived);
}
