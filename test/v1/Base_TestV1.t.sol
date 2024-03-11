// SPDX-License-Identifier: MIT
pragma solidity 0.8.20;

import {IHorseStore} from "../../src/horseStoreV1/IHorseStore.sol";
import {HorseStore} from "../../src/horseStoreV1/HorseStore.sol";
import {Test, console2} from "forge-std/Test.sol";

abstract contract Base_TestV1 is Test {
    IHorseStore public horseStore;

    function setUp() public virtual {
        horseStore = IHorseStore(address(new HorseStore()));
    }

    function testReadValue() public {
        uint256 initialHorseNumber = horseStore.readNumberOfHorses();
        assertEq(initialHorseNumber, 0);
    }

    function testWriteValue() public {
        uint256 numberOfHorses = 777;
        horseStore.updateHorseNumber(numberOfHorses);
        assertEq(horseStore.readNumberOfHorses(), numberOfHorses);
    }

    function testFuzzWriteValue(uint256 numberOfHorses) public {
        horseStore.updateHorseNumber(numberOfHorses);
        assertEq(horseStore.readNumberOfHorses(), numberOfHorses);
    }
}