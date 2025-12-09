import Control.Monad
import Data.Array.IO
import Data.IORef
import System.CPUTime

main :: IO ()
main = do
  let n = 1000000
  let iter = 100

  start <- getCPUTime -- tiempo inicial
  curArr <- newArray (0, n - 1) 0.0 :: IO (IOUArray Int Double)
  nextArr <- newArray (0, n - 1) 0.0 :: IO (IOUArray Int Double)

  curRef <- newIORef curArr
  nextRef <- newIORef nextArr

  writeArray curArr (n `div` 2) 100.0

  forM_ [1 .. iter] $ \_ -> do
    cur <- readIORef curRef
    next <- readIORef nextRef

    forM_ [1 .. n - 2] $ \i -> do
      a <- readArray cur (i - 1)
      b <- readArray cur i
      c <- readArray cur (i + 1)
      writeArray next i ((a + b + c) / 3.0)

    writeArray next 0 0.0
    writeArray next (n - 1) 0.0

    writeIORef curRef next
    writeIORef nextRef cur

  end <- getCPUTime -- tiempo final
  let diff = fromIntegral (end - start) / (10 ^ 12) :: Double

  finalArr <- readIORef curRef
  center <- readArray finalArr (n `div` 2)

  putStrLn $ "Temperatura en el centro: " ++ show center
  putStrLn $ "Tiempo de ejecución: " ++ show diff ++ " segundos"
