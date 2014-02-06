import blueunittest
import trinity
import blue
import test_trinity

class TestTextureAtlas(blueunittest.TestCase):
    """
    A set of test cases for texture atlassing.
    """


    def setUp(self):
        test_trinity.SetupDeviceIfNeeded()
        trinity.textureAtlasMan.AddAtlas(trinity.PIXEL_FORMAT.B8G8R8A8_UNORM, 1024, 1024)
        self.atlas = trinity.textureAtlasMan.atlases[0]


    def tearDown(self):
        self.atlas = None
        trinity.textureAtlasMan.RemoveAtlas(trinity.PIXEL_FORMAT.B8G8R8A8_UNORM)


    def test_CreateAndDeleteSmallTextureVerifyingRefCountStaysAtZero(self):
        d = blue.classes.LiveCount()
        refCountBefore = d["trinity.Tr2AtlasTexture"]

        x = self.atlas.CreateTexture(8, 8)
        del x

        d = blue.classes.LiveCount()
        self.assertEqual(d["trinity.Tr2AtlasTexture"], refCountBefore)


    def test_CreateSmallTexture(self):
        """
        Test the basics of creating an atlas texture.
        """

        x = self.atlas.CreateTexture(8, 8)

        # Ensure atlas association is correct
        self.assertEqual(x.atlas, self.atlas)

        # Ensure dimensions are what we asked for
        self.assertEqual(x.width, 8)
        self.assertEqual(x.height, 8)

        # The texture should not be stand alone
        self.assertFalse(x.isStandAlone)

        self.assertEqual(x.resPath, "")

        self.assertEqual(x.atlasWidth, self.atlas.width)
        self.assertEqual(x.atlasHeight, self.atlas.height)

        lockInfo = x.LockBuffer()
        address, width, height, pitch = lockInfo

        self.assertEqual(width, 8)
        self.assertEqual(height, 8)

        x.UnlockBuffer()

        self.assertEqual(self.atlas.texturesInAtlasCount, 1)
        self.assertEqual(self.atlas.texturesOutsideAtlasCount, 0)

        del x
        self.assertEqual(self.atlas.texturesInAtlasCount, 0)
        self.assertEqual(self.atlas.texturesOutsideAtlasCount, 0)

    
    def test_InterleavedLocking(self):
        """
        Test error handling for locking multiple textures (which is not allowed)
        """
        if trinity.platform == "dx11":
            self.skipTest("Not applicable on this platform")
        
        x = self.atlas.CreateTexture(8, 8)
        y = self.atlas.CreateTexture(8, 8)

        # Make sure both textures are insiders
        self.assertEqual(self.atlas.texturesInAtlasCount, 2)
        self.assertEqual(self.atlas.texturesOutsideAtlasCount, 0)

        lockInfoX = x.LockBuffer()
        lockInfoY = y.LockBuffer()

        # At the moment, locking two textures will not raise an exception, but lockInfoY
        # will be False, rather than a tuple
        self.assertEqual(len(lockInfoX), 4)
        self.assertFalse(lockInfoY)

        x.UnlockBuffer()
        y.UnlockBuffer()

        # Double check that we can lock after cleaning up the previous locks
        lockInfoX = x.LockBuffer()
        self.assertEqual(len(lockInfoX), 4)
        x.UnlockBuffer()


    def test_InterleaveLockAndCreate(self):
        """
        Create a texture while another texture holds a lock
        """

        x = self.atlas.CreateTexture(8, 8)

        lockInfoX = x.LockBuffer()

        y = self.atlas.CreateTexture(8, 8)

        # Ensure dimensions are what we asked for
        self.assertEqual(y.width, 8)
        self.assertEqual(y.height, 8)

        x.UnlockBuffer()


    def test_Outsiders(self):
        """
        Create a large texture, too large for the atlas
        """

        x = self.atlas.CreateTexture(1024, 1024)

        # Ensure atlas association is correct
        self.assertEqual(x.atlas, self.atlas)

        # Ensure dimensions are what we asked for
        self.assertEqual(x.width, 1024)
        self.assertEqual(x.height, 1024)

        # The texture should not be stand alone
        self.assertFalse(x.isStandAlone)

        self.assertEqual(x.resPath, "")

        self.assertEqual(x.atlasWidth, self.atlas.width)
        self.assertEqual(x.atlasHeight, self.atlas.height)

        lockInfo = x.LockBuffer()
        address, width, height, pitch = lockInfo

        self.assertEqual(width, 1024)
        self.assertEqual(height, 1024)

        x.UnlockBuffer()

        self.assertEqual(self.atlas.texturesInAtlasCount, 0)
        self.assertEqual(self.atlas.texturesOutsideAtlasCount, 1)

        del x
        self.assertEqual(self.atlas.texturesInAtlasCount, 0)
        self.assertEqual(self.atlas.texturesOutsideAtlasCount, 0)


    def test_StandAlone(self):
        """
        Create a texture, set as stand-alone
        """

        x0 = self.atlas.CreateTexture(64, 64)
        x = self.atlas.CreateTexture(32, 64)


        # Ensure atlas association is correct
        self.assertEqual(x.atlas, self.atlas)

        self.assertEqual(self.atlas.texturesInAtlasCount, 2)
        self.assertEqual(self.atlas.texturesOutsideAtlasCount, 0)

        x.isStandAlone = True

        # Ensure atlas association is still intact
        self.assertEqual(x.atlas, self.atlas)

        # Locking should work, even if it is stand-alone
        lockInfo = x.LockBuffer()
        address, width, height, pitch = lockInfo

        self.assertEqual(width, 32)
        self.assertEqual(height, 64)

        x.UnlockBuffer()

        self.assertEqual(self.atlas.texturesInAtlasCount, 1)
        self.assertEqual(self.atlas.texturesOutsideAtlasCount, 1)



    def test_AddingManyTexturesShouldOverflow(self):
        """
        Create a bunch of textures to have the atlas overflow
        """

        self.assertEqual(self.atlas.texturesInAtlasCount, 0)

        textures = []
        for i in xrange(10):
            textures.append(self.atlas.CreateTexture(256, 256))

        self.assertTrue(self.atlas.texturesInAtlasCount > 0)
        self.assertTrue(self.atlas.texturesOutsideAtlasCount > 0)


    def test_AddingManyTexturesCausingOverflowThenDeleting(self):

        self.assertEqual(self.atlas.texturesInAtlasCount, 0)

        textures = []
        for i in xrange(10):
            textures.append(self.atlas.CreateTexture(256, 256))

        # Delete all but the first two textures
        del textures[2:]

        # Those textures should be resident in the atlas
        self.assertEqual(self.atlas.texturesInAtlasCount, 2)
        self.assertEqual(self.atlas.texturesOutsideAtlasCount, 0)


    def test_AddingManyTexturesCausingOverflowThenDeleting(self):

        self.assertEqual(self.atlas.texturesInAtlasCount, 0)

        textures = []
        for i in xrange(10):
            textures.append(self.atlas.CreateTexture(256, 256))

        # We should have outsiders at this point
        self.assertTrue(self.atlas.texturesOutsideAtlasCount > 0)

        # Delete all but the last texture
        del textures[:-1]

        # Those textures should be resident in the atlas
        self.assertEqual(self.atlas.texturesInAtlasCount, 1)
        self.assertEqual(self.atlas.texturesOutsideAtlasCount, 0)


    def test_Stats(self):
        self.assertEqual(self.atlas.GetFreeTexels(), self.atlas.width*self.atlas.height)
        self.assertEqual(self.atlas.GetFreeTexelPercentage(), 1.0)

        self.assertEqual(self.atlas.GetFreeMaxWidth(), self.atlas.width)
        self.assertEqual(self.atlas.GetFreeMaxHeight(), self.atlas.height)

        x = self.atlas.CreateTexture(32, 64)

        self.assertTrue(self.atlas.GetFreeTexels() < self.atlas.width*self.atlas.height)
        self.assertTrue(self.atlas.GetFreeTexelPercentage() < 1.0)


