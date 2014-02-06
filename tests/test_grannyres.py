import unittest
import trinity
import blue

import test_trinity

class TestGrannyRes(unittest.TestCase):
    """
    A set of test cases for TriGrannyRes. This is primarily intended
    for regression testing render steps while converting exposed methods.
    """
    def setUp(self):
        test_trinity.SetupDeviceIfNeeded()

    def tearDown(self):
        trinity.device.InvalidateAndUnregisterForTicks()

    def GetAb1Geometry(self):
        blue.motherLode.clear()
        res = blue.resMan.GetResource("../../eve/client/res/dx9/model/ship/amarr/battleship/ab1/ab1_t1.gr2", "raw")
        blue.resMan.Wait()
        self.assertTrue(res.isGood)
        return res

    def testCreateGeometryRes(self):
        x = trinity.TriGrannyRes()
        y = x.CreateGeometryRes()
        self.assertEqual(trinity.TriGeometryRes, type(y))

    def testBakeBlendshape_Empty(self):
        x = trinity.TriGrannyRes()
        self.assertRaises(RuntimeError, x.BakeBlendshape, 0, [1], None)

    def testGetMeshCount_Empty(self):
        x = trinity.TriGrannyRes()
        n = x.GetMeshCount()
        self.assertEqual(0, n)

    def testGetMeshCount(self):
        x = self.GetAb1Geometry()
        n = x.GetMeshCount()
        self.assertEqual(1, n)

    def testGetMeshAreaCount_Empty(self):
        x = trinity.TriGrannyRes()
        self.assertRaises(RuntimeError, x.GetMeshAreaCount, 0)

    def testGetMeshAreaCount(self):
        x = self.GetAb1Geometry()
        n = x.GetMeshAreaCount(0)
        self.assertEqual(2, n)

    def testGetMeshAreaCount_OutOfRange(self):
        x = self.GetAb1Geometry()
        self.assertRaises(RuntimeError, x.GetMeshAreaCount, 1)

    def testGetMeshName_Empty(self):
        x = trinity.TriGrannyRes()
        self.assertRaises(RuntimeError, x.GetMeshName, 0)

    def testGetMeshName(self):
        x = self.GetAb1Geometry()
        name = x.GetMeshName(0)
        self.assertEqual("pipeline1:defaultShape", name)

    def testGetMeshName_OutOfRange(self):
        x = self.GetAb1Geometry()
        self.assertRaises(RuntimeError, x.GetMeshName, 1)

    def testGetMeshMorphCount_Empty(self):
        x = trinity.TriGrannyRes()
        self.assertRaises(RuntimeError, x.GetMeshMorphCount, 0)

    def testGetMeshName(self):
        x = self.GetAb1Geometry()
        n = x.GetMeshMorphCount(0)
        self.assertEqual(0, n)

    def testGetMeshName_OutOfRange(self):
        x = self.GetAb1Geometry()
        self.assertRaises(RuntimeError, x.GetMeshMorphCount, 1)

