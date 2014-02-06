import unittest
import trinity
import blue

import test_trinity

class TestGeometryRes(unittest.TestCase):
    """
    A set of test cases for TriGeometryRes. This is primarily intended
    for regression testing render steps while converting exposed methods.
    """
    def setUp(self):
        test_trinity.SetupDeviceIfNeeded()

    def tearDown(self):
        trinity.device.InvalidateAndUnregisterForTicks()

    def GetAb1Geometry(self):
        blue.motherLode.clear()
        res = blue.resMan.GetResource("../../eve/client/res/dx9/model/ship/amarr/battleship/ab1/ab1_t1.gr2")
        blue.resMan.Wait()
        self.assertTrue(res.isGood)
        return res

    def testGetModelCount_Empty(self):
        res = trinity.TriGeometryRes()
        n = res.GetModelCount()
        self.assertEqual(0, n)

    def testGetModelCount(self):
        res = self.GetAb1Geometry()
        n = res.GetModelCount()
        self.assertEqual(1, n)

    def testGetModelName_Empty(self):
        res = trinity.TriGeometryRes()
        self.assertRaises(RuntimeError, res.GetModelName, 0)

    def testGetModelName(self):
        res = self.GetAb1Geometry()
        name = res.GetModelName(0)
        self.assertEqual("pipeline1:default1", name)

    def testGetMeshCount_Empty(self):
        res = trinity.TriGeometryRes()
        n = res.GetMeshCount()
        self.assertEqual(0, n)

    def testGetMeshCount(self):
        res = self.GetAb1Geometry()
        n = res.GetMeshCount()
        self.assertEqual(1, n)

    def testGetMeshName_Empty(self):
        res = trinity.TriGeometryRes()
        self.assertRaises(RuntimeError, res.GetMeshName, 0)

    def testGetMeshName(self):
        res = self.GetAb1Geometry()
        name = res.GetMeshName(0)
        self.assertEqual("pipeline1:defaultShape", name)

    def testGetMeshAreaCount_Empty(self):
        res = trinity.TriGeometryRes()
        self.assertRaises(RuntimeError, res.GetMeshAreaCount, 0)

    def testGetMeshAreaCount(self):
        res = self.GetAb1Geometry()
        n = res.GetMeshAreaCount(0)
        self.assertEqual(2,n)

    def testGetMeshAreaName_Empty(self):
        res = trinity.TriGeometryRes()
        self.assertRaises(RuntimeError, res.GetMeshAreaName, 0, 0)

    def testGetMeshAreaName_AreaOutOfRange(self):
        res = self.GetAb1Geometry()
        self.assertRaises(RuntimeError, res.GetMeshAreaName, 0, 4)

    def testGetMeshAreaName(self):
        res = self.GetAb1Geometry()
        name = res.GetMeshAreaName(0, 0)
        self.assertEqual("Hull", name)

    def testGetAreaBoundingBox_Empty(self):
        res = trinity.TriGeometryRes()
        self.assertRaises(RuntimeError, res.GetAreaBoundingBox, 0, 0)

    def testGetAreaBoundingBox_AreaOutOfRange(self):
        res = self.GetAb1Geometry()
        self.assertRaises(RuntimeError, res.GetAreaBoundingBox, 0, 4)

    def testGetAreaBoundingBox(self):
        res = self.GetAb1Geometry()
        min, max = res.GetAreaBoundingBox(0, 0)

    def testGetRayAreaIntersection_Empty(self):
        res = trinity.TriGeometryRes()
        found, result = res.GetRayAreaIntersection(
            (0,0,0),
            (0,0,1),
            0,
            0,
            trinity.TriGeometryCollisionResultFlags.ANY,
            trinity.TriGeometryCollisionCullingFlags.NONE)

    def testGetBoundingBox_Empty(self):
        res = trinity.TriGeometryRes()
        self.assertRaises(RuntimeError, res.GetBoundingBox, 0)

    def testGetBoundingBox(self):
        res = self.GetAb1Geometry()
        min, max = res.GetBoundingBox(0)
        self.assertGreaterEqual(max[0], min[0])
        self.assertGreaterEqual(max[1], min[1])
        self.assertGreaterEqual(max[2], min[2])

    def testGetBoundingBox_OutOfRange(self):
        res = self.GetAb1Geometry()
        self.assertRaises(RuntimeError, res.GetBoundingBox, 1)

