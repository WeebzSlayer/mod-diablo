DELETE FROM `npc_vendor` WHERE `entry` = 99000;
INSERT INTO `npc_vendor` (`entry`, `slot`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(99000, 1, 27230, 0, 0, 0), -- Super Healing Potion
(99000, 2, 27239, 0, 0, 0); -- Super Mana Potion