/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
DROP TABLE IF EXISTS `skill_extra_item_template`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `skill_extra_item_template` 
(
  `spellId` mediumint(8) unsigned NOT NULL DEFAULT '0' COMMENT 'SpellId of the item creation spell',
  `requiredSpecialization` mediumint(8) unsigned NOT NULL DEFAULT '0' COMMENT 'Specialization spell id',
  `additionalCreateChance` float NOT NULL DEFAULT '0' COMMENT 'chance to create add',
  `newMaxOrEntry` mediumint(8) NOT NULL DEFAULT '0',
  PRIMARY KEY (`spellId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Skill Specialization System';
/*!40101 SET character_set_client = @saved_cs_client */;

LOCK TABLES `skill_extra_item_template` WRITE;
/*!40000 ALTER TABLE `skill_extra_item_template` DISABLE KEYS */;
INSERT INTO `skill_extra_item_template` VALUES 
(2329,28677,14,4),
(2331,28675,14,4),
(2332,28675,14,4),
(2333,28677,14,4),
(2334,28677,14,4),
(2335,28675,14,4),
(2337,28675,14,4),
(3170,28677,14,4),
(3171,28677,14,4),
(3172,28675,14,4),
(3173,28675,14,4),
(3174,28675,14,4),
(3175,28675,14,4),
(3176,28677,14,4),
(3177,28677,14,4),
(3188,28677,14,4),
(3230,28677,14,4),
(3447,28675,14,4),
(3448,28675,14,4),
(3450,28677,14,4),
(3451,28677,14,4),
(3452,28675,14,4),
(3453,28677,14,4),
(4508,28675,14,4),
(4942,28675,14,4),
(6617,28675,14,4),
(6618,28675,14,4),
(6624,28675,14,4),
(7179,28677,14,4),
(7181,28675,14,4),
(7183,28677,14,4),
(7255,28675,14,4),
(7256,28675,14,4),
(7257,28675,14,4),
(7258,28675,14,4),
(7259,28675,14,4),
(7841,28675,14,4),
(7845,28677,14,4),
(8240,28677,14,4),
(11448,28675,14,4),
(11449,28677,14,4),
(11450,28677,14,4),
(11452,28675,14,4),
(11453,28675,14,4),
(11457,28675,14,4),
(11458,28675,14,4),
(11460,28677,14,4),
(11461,28677,14,4),
(11464,28675,14,4),
(11465,28677,14,4),
(11466,28677,14,4),
(11467,28677,14,4),
(11468,28677,14,4),
(11472,28677,14,4),
(11476,28677,14,4),
(11477,28677,14,4),
(11478,28677,14,4),
(11479,28672,16,4),
(11480,28672,16,4),
(12609,28677,14,4),
(15833,28675,14,4),
(17187,28672,16,4),
(17552,28675,14,4),
(17554,28677,14,4),
(17555,28677,14,4),
(17557,28677,14,4),
(17559,28672,16,4),
(17560,28672,16,4),
(17561,28672,16,4),
(17562,28672,16,4),
(17563,28672,16,4),
(17564,28672,16,4),
(17565,28672,16,4),
(17566,28672,16,4),
(17570,28675,14,4),
(17571,28677,14,4),
(17572,28675,14,4),
(17573,28677,14,4),
(17574,28675,14,4),
(17575,28675,14,4),
(17576,28675,14,4),
(17577,28675,14,4),
(17578,28675,14,4),
(17580,28675,14,4),
(17634,28677,14,4),
(17635,28677,14,4),
(17636,28677,14,4),
(17637,28677,14,4),
(17638,28677,14,4),
(18560,26798,100,1),
(21923,28677,14,4),
(22732,28675,14,4),
(22808,28677,14,4),
(24365,28677,14,4),
(24366,28675,14,4),
(24367,28675,14,4),
(24368,28677,14,4),
(25146,28672,16,4),
(26277,28677,14,4),
(26751,26798,100,1),
(28543,28677,14,4),
(28544,28677,14,4),
(28545,28677,14,4),
(28546,28675,14,4),
(28549,28677,14,4),
(28550,28675,14,4),
(28552,28677,14,4),
(28553,28677,14,4),
(28554,28675,14,4),
(28555,28675,14,4),
(28556,28677,14,4),
(28557,28677,14,4),
(28558,28677,14,4),
(28562,28675,14,4),
(28563,28675,14,4),
(28564,28675,14,4),
(28565,28675,14,4),
(28566,28672,16,4),
(28567,28672,16,4),
(28568,28672,16,4),
(28569,28672,16,4),
(28570,28677,14,4),
(28571,28675,14,4),
(28572,28675,14,4),
(28573,28675,14,4),
(28575,28675,14,4),
(28576,28675,14,4),
(28577,28675,14,4),
(28578,28677,14,4),
(28579,28675,14,4),
(28580,28672,16,4),
(28581,28672,16,4),
(28582,28672,16,4),
(28583,28672,16,4),
(28584,28672,16,4),
(28585,28672,16,4),
(28586,28675,14,4),
(28587,28677,14,4),
(28588,28677,14,4),
(28589,28677,14,4),
(28590,28677,14,4),
(28591,28677,14,4),
(29688,28672,16,4),
(31373,26797,100,1),
(32765,28672,16,4),
(32766,28672,16,4),
(33732,28675,14,4),
(33733,28675,14,4),
(33738,28677,14,4),
(33740,28677,14,4),
(33741,28677,14,4),
(36686,26801,100,1),
(38960,28677,14,4),
(38961,28675,14,4),
(38962,28675,14,4),
(39636,28677,14,4),
(39637,28677,14,4),
(39638,28677,14,4),
(39639,28677,14,4),
(42736,28677,14,4),
(45061,28675,14,4),
(53771,28672,16,3),
(53773,28672,16,3),
(53774,28672,16,3),
(53775,28672,16,3),
(53776,28672,16,3),
(53777,28672,16,3),
(53779,28672,16,3),
(53780,28672,16,3),
(53781,28672,16,3),
(53782,28672,16,3),
(53783,28672,16,3),
(53784,28672,16,3),
(53831,55534,20,-41432),
(53832,55534,20,-41434),
(53834,55534,20,-41438),
(53835,55534,20,-41433),
(53836,28675,16,4),
(53837,28675,16,4),
(53838,28675,16,4),
(53839,28675,16,4),
(53840,28677,17,4),
(53841,28677,16,4),
(53842,28677,17,4),
(53843,55534,20,-41439),
(53844,55534,20,-41435),
(53845,55534,20,-41436),
(53847,28677,17,4),
(53848,28677,17,4),
(53852,55534,20,-41444),
(53853,55534,20,-41448),
(53854,55534,20,-41447),
(53855,55534,20,-41449),
(53856,55534,20,-41446),
(53857,55534,20,-41445),
(53859,55534,20,-41461),
(53860,55534,20,-41460),
(53861,55534,20,-41462),
(53862,55534,20,-41452),
(53863,55534,20,-41457),
(53864,55534,20,-41459),
(53865,55534,20,-41455),
(53866,55534,20,-41450),
(53867,55534,20,-41454),
(53868,55534,20,-41458),
(53869,55534,20,-41451),
(53870,55534,20,-41456),
(53871,55534,20,-41453),
(53872,55534,20,-41492),
(53873,55534,20,-41488),
(53874,55534,20,-41483),
(53875,55534,20,-41499),
(53876,55534,20,-41489),
(53877,55534,20,-41484),
(53878,55534,20,-41491),
(53879,55534,20,-41493),
(53880,55534,20,-41485),
(53881,55534,20,-41494),
(53882,55534,20,-41495),
(53883,55534,20,-41502),
(53884,55534,20,-41486),
(53885,55534,20,-41497),
(53886,55534,20,-41429),
(53887,55534,20,-41496),
(53888,55534,20,-41487),
(53889,55534,20,-41501),
(53890,55534,20,-41500),
(53891,55534,20,-41490),
(53892,55534,20,-41482),
(53893,55534,20,-41498),
(53894,55534,20,-41479),
(53895,28675,16,4),
(53898,28677,17,4),
(53899,28677,17,8),
(53900,28675,16,4),
(53901,28677,17,8),
(53902,28677,17,8),
(53903,28677,17,8),
(53904,28675,16,4),
(53905,28675,16,4),
(53916,55534,20,-41468),
(53917,55534,20,-41481),
(53918,55534,20,-41464),
(53919,55534,20,-41476),
(53920,55534,20,-41466),
(53921,55534,20,-41473),
(53922,55534,20,-41470),
(53923,55534,20,-41475),
(53924,55534,20,-41480),
(53925,55534,20,-41467),
(53926,55534,20,-41463),
(53927,55534,20,-41477),
(53928,55534,20,-41469),
(53929,55534,20,-41471),
(53930,55534,20,-41465),
(53931,55534,20,-41472),
(53932,55534,20,-41478),
(53933,55534,20,-41474),
(53934,55534,20,-41441),
(53936,28675,16,4),
(53937,28675,16,4),
(53938,28675,16,4),
(53939,28675,16,4),
(53940,55534,20,-41442),
(53941,55534,20,-41440),
(53942,28675,16,4),
(53943,55534,20,-41443),
(54017,55534,20,-41437),
(54213,28677,17,8),
(54218,28677,17,4),
(54220,28677,17,4),
(54221,28675,16,4),
(54222,28675,16,4),
(56001,26798,100,1),
(56002,26801,100,1),
(56003,26797,100,1),
(56519,28677,17,4),
(57425,28672,16,3),
(57427,28672,16,3),
(58868,28675,16,4),
(58871,28675,16,4),
(60350,28672,16,5),
(60354,28677,17,4),
(60355,28677,17,4),
(60356,28677,17,4),
(60357,28677,17,4),
(60365,28677,17,4),
(60366,28677,17,4),
(60367,28677,17,4),
(62213,28677,14,4),
(62410,28677,17,4),
(66658,28672,16,3),
(66659,28672,16,3),
(66660,28672,16,3),
(66662,28672,16,3),
(66663,28672,16,3),
(66664,28672,16,3),
(67025,28677,17,8);
/*!40000 ALTER TABLE `skill_extra_item_template` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
