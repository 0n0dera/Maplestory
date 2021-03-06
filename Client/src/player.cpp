#include "player.h"
#include "fixed_camera.h"
#include <iostream>

Player::Player(
		glm::vec3 position,
		GLfloat speed,
		GLfloat yaw,
		GLfloat pitch,
		GLfloat roll)
		: Entity(position, speed, yaw, pitch, roll, constants::PLAYER_BB_X, constants::PLAYER_BB_Y, constants::PLAYER_BB_Z) {}

Player::~Player() {}

void Player::Move(EntityMovement direction, GLfloat delta) {
    if (recoiling) return;
    const GLfloat turnRight = -glm::half_pi<GLfloat>();
    const GLfloat turnLeft = glm::half_pi<GLfloat>();
    const GLfloat turnBack = glm::pi<GLfloat>();
    static EntityMovement last = FORWARD;
    if (direction != last) {
        switch (last) {
        case FORWARD:
            switch (direction) {
            case BACKWARD:
                nextYaw += turnBack;
                break;
            case RIGHT:
                nextYaw += turnRight;
                break;
            case LEFT:
                nextYaw += turnLeft;
                break;
            }
            break;
        case BACKWARD:
            switch (direction) {
            case FORWARD:
                nextYaw += turnBack;
                break;
            case RIGHT:
                nextYaw += turnLeft;
                break;
            case LEFT:
                nextYaw += turnRight;
                break;
            }
            break;
        case RIGHT:
            switch (direction) {
            case BACKWARD:
                nextYaw += turnRight;
                break;
            case FORWARD:
                nextYaw += turnLeft;
                break;
            case LEFT:
                nextYaw += turnBack;
                break;
            }
            break;
        case LEFT:
            switch (direction) {
            case RIGHT:
                nextYaw += turnBack;
                break;
            case BACKWARD:
                nextYaw += turnLeft;
                break;
            case FORWARD:
                nextYaw += turnRight;
                break;
            }
            break;
        }
    }
    last = direction;
	// need to update camera distance when player moves
	// camera needs to jump behind player
	Entity::Move(direction, delta);
}

void Player::Collide(Entity* entity) {
    auto recoilVec = glm::normalize(position - entity->position);
    // if enemy, recoil
    Recoil(recoilVec);
}

void Player::Recoil(const glm::vec3& recoilVec) {
    recoiling = true;
    ambientMovement.x = recoilVec.x * 2;
    ambientMovement.y = 2.0f;
    ambientMovement.z = recoilVec.z * 2;
}

void Player::Jump(float yVel) {
    Entity::Jump(yVel);
}
