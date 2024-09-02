#include "pch.h"
#include "../Project10/Animation.h"
#include "../Project10/Libs.h"
TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(TestCaseName, CheckingPositionOfAnimation) {
	std::unique_ptr<sf::RenderTexture> target = std::make_unique<sf::RenderTexture>();
	std::unique_ptr<Animation> testAnimation = std::make_unique<Animation>("images/flowers/sprite_flower", 9, 1, target.get());
	testAnimation->moveTo(20, 20);
	EXPECT_EQ(sf::Vector2f(20, 20), testAnimation->getPosition());
	EXPECT_TRUE(true);
}
//To run if here's to much exceptions - _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING