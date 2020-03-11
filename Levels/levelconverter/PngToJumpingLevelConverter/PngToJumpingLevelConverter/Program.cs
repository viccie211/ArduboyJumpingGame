using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;

namespace PngToJumpingLevelConverter
{
    class Program
    {
        public const string InputPath = "C:\\Git\\Arduino\\Arduboy\\Jumping\\1-1.png";
        public const string OutputPath = "C:\\Git\\Arduino\\Arduboy\\Jumping\\";
        public const string LevelName = "OneDashOne";
        public static int Height = 0;
        public static int Width = 0;
        static void Main(string[] args)
        {
            List<Color> colors = new List<Color>();
            List<List<int>> level = new List<List<int>>();
            using (var image = new Bitmap(System.Drawing.Image.FromFile(InputPath)))
            {
                Height = image.Height;
                Width = image.Width;
                for (int y = 0; y < Height; y++)
                {
                    if (y > 0)
                    {
                        level.Add(new List<int>());
                    }
                    for (int x = 0; x < Width; x++)
                    {
                        Color pixelColor = image.GetPixel(x, y);

                        //determine the palette of the image which should be located on the very first row.
                        if (y == 0)
                        {
                            if (!colors.Contains(pixelColor))
                            {
                                colors.Add(pixelColor);
                            }
                        }
                        else
                        {
                            level[y - 1].Add(colors.IndexOf(pixelColor));
                        }
                    }
                }

            }

            StringBuilder resultFile = new StringBuilder($"const byte {LevelName}[{Height - 1}][{Width}] PROGMEM = \r\n{'{'}\r\n");
            for (int y = 0; y < Height - 1; y++)
            {
                resultFile.Append("\t{\r\n\t\t");
                for (int x = 0; x < Width; x++)
                {
                    resultFile.Append($"{level[y][x]}, ");
                }
                resultFile.Append("\r\n\t},\r\n");
            }
            resultFile.Append("};");
            System.IO.File.WriteAllText($"{OutputPath}\\{LevelName}.txt", resultFile.ToString());
        }
    }
}
