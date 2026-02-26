#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <string>

namespace TestFramework {

    struct TestResult {
        std::string name;
        bool passed;
        std::string message;
    };

    class TestRunner {
    public:
        using TestCase = std::function<void()>;

        static TestRunner& Get() {
            static TestRunner instance;
            return instance;
        }

        void AddTest(const std::string& name, TestCase test) {
            m_tests.push_back({name, test});
        }

        int Run() {
            int passed = 0;
            int failed = 0;
            std::cout << "Running " << m_tests.size() << " tests..." << std::endl;

            for (const auto& testPair : m_tests) {
                m_currentTestName = testPair.first;
                m_currentTestPassed = true;
                m_currentTestMessage = "";

                try {
                    testPair.second();
                } catch (const std::exception& e) {
                    m_currentTestPassed = false;
                    m_currentTestMessage = "Exception: " + std::string(e.what());
                } catch (...) {
                    m_currentTestPassed = false;
                    m_currentTestMessage = "Unknown Exception";
                }

                if (m_currentTestPassed) {
                    std::cout << "[PASS] " << testPair.first << std::endl;
                    passed++;
                } else {
                    std::cout << "[FAIL] " << testPair.first << " - " << m_currentTestMessage << std::endl;
                    failed++;
                }
            }

            std::cout << "\nResults: " << passed << " passed, " << failed << " failed." << std::endl;
            return failed > 0 ? 1 : 0;
        }

        void Assert(bool condition, const std::string& message) {
            if (!condition) {
                m_currentTestPassed = false;
                m_currentTestMessage = message;
                throw std::runtime_error(message); // Stop current test
            }
        }

    private:
        std::vector<std::pair<std::string, TestCase>> m_tests;
        std::string m_currentTestName;
        bool m_currentTestPassed;
        std::string m_currentTestMessage;
    };

    #define TEST_CASE(name) \
        void name(); \
        struct name##_Register { \
            name##_Register() { TestFramework::TestRunner::Get().AddTest(#name, name); } \
        } name##_register_inst; \
        void name()

    #define ASSERT_TRUE(condition) TestFramework::TestRunner::Get().Assert((condition), "Assertion failed: " #condition)
    #define ASSERT_EQ(a, b) TestFramework::TestRunner::Get().Assert((a) == (b), "Assertion failed: " #a " == " #b)

}
