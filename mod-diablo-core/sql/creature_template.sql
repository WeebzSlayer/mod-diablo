-- 1. Create the NPC Persephone
DELETE FROM `creature_template` WHERE `entry` = 99000;
INSERT INTO `creature_template` (`entry`, `modelid1`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `unit_class`, `ScriptName`) VALUES
(99000, 26305, 'Persephone', 'Rift Harbinger', 'SpeakTo', 0, 80, 80, 35, 129, 1, 1.14, 1, 1, 'npc_persephone');

-- 2. Create the Rift Guardian (Example)
DELETE FROM `creature_template` WHERE `entry` = 99001;
INSERT INTO `creature_template` (`entry`, `modelid1`, `name`, `subname`, `minlevel`, `maxlevel`, `faction`, `scale`, `unit_class`, `rank`, `exp`) VALUES
(99001, 24996, 'Rift Guardian', 'The Unforgiven', 83, 83, 14, 2.5, 1, 3, 3);