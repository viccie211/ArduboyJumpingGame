using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;

namespace PngToJumpingLevelConverter
{
    class Program
    {
        public const string InputPath = "D:\\Games\\Repos\\ArduboyJumpingGame\\Levels\\png\\1-1.png";
        public const string OutputPath = "D:\\Games\\Repos\\ArduboyJumpingGame\\Levels\\txt";
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

            StringBuilder resultFile = new StringBuilder($"const byte {LevelName}[{Height - 1}][{Width/4}] PROGMEM = \r\n{'{'}\r\n");
            for (int y = 0; y < Height - 1; y++)
            {
                resultFile.Append("\t{\r\n\t\t");
                for (int x = 0; x < Width; x+=4)
                {
                    resultFile.Append("0b");
                    for (int i = x; i < x + 4; i++)
                    {
                        var bitString = Convert.ToString(level[y][i], 2);
                        if (bitString.Length < 2)
                        {
                            bitString = $"0{bitString}";
                        }
                        resultFile.Append($"{bitString}");    
                    }

                    resultFile.Append(", ");
                }
                resultFile.Append("\r\n\t},\r\n");
            }
            resultFile.Append("};");
            System.IO.File.WriteAllText($"{OutputPath}\\{LevelName}.txt", resultFile.ToString());
        }
    }
}
