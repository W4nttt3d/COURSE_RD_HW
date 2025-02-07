#pragma once
enum class TileTypeStatus
{
    NONE,
    HARVEST,
    RESOURCE_TRANSFER,
};
class TileStatus 
{
public:
    bool isBlocked = false; 
    TileTypeStatus currentTaskType = TileTypeStatus::NONE;

    void block(TileTypeStatus taskType) {
        isBlocked = true;
        currentTaskType = taskType;
    }

    void unblock() {
        isBlocked = false;
        currentTaskType = TileTypeStatus::NONE;
    }
};
