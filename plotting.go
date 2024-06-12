package main

import (
	"image/color"
	"io/fs"
	"log"
	"math"
	"os"
	"path/filepath"
	"strconv"

	"github.com/gocarina/gocsv"
	"github.com/kim89098/slice"
	"gonum.org/v1/gonum/floats"
	"gonum.org/v1/plot"
	"gonum.org/v1/plot/plotter"
	"gonum.org/v1/plot/vg"
	"gonum.org/v1/plot/vg/draw"
)

var COLOURS = []color.RGBA{
	{R: 255, A: 255},
	{B: 255, A: 255},
	{G: 255, A: 255},
	{R: 255, G: 128, A: 255},
	{R: 127, B: 255, A: 255},
	{R: 255, B: 127, A: 255},
}

func RootPath() string {

	ex, err := os.Executable()
	if err != nil {
		panic(err)
	}

	return filepath.Join(filepath.Dir(ex), "..")
}

func ReconstructData(input []map[string]string) map[string][]float64 {
	output := make(map[string][]float64)

	for _, subMap := range input {
		for key, value := range subMap {
			if _, ok := output[key]; ok {
				entry, _ := strconv.ParseFloat(value, 64)
				output[key] = append(output[key], entry)
			} else {
				entry, _ := strconv.ParseFloat(value, 64)
				output[key] = []float64{entry}
			}
		}
	}

	delete(output, "")

	return output
}

func MakePlotter(xValues []float64, yValues []float64) (plotter.XYs, plotter.XYs) {
	pts := make(plotter.XYs, len(xValues))
	ptsLog := make(plotter.XYs, len(xValues))

	for i, xy := range slice.Zip(xValues, yValues) {

		x := xy.A
		y := xy.B

		pts[i].Y = y
		ptsLog[i].Y = y + 1

		pts[i].X = x
		ptsLog[i].X = x

	}

	return pts, ptsLog
}

func MakeXAxis(scale []float64) plot.ConstantTicks {
	ticks := make([]plot.Tick, len(scale))

	for i, value := range scale {
		ticks[i].Value = float64(value)
		ticks[i].Label = strconv.FormatUint(uint64(value), 10)
	}

	return plot.ConstantTicks(ticks)
}

func PlotData(subDirName string, fileName string, data map[string][]float64) {

	linearPlot := plot.New()
	logPlot := plot.New()

	nElements := data["elements"]
	xaxis := MakeXAxis(nElements)

	linearPlot.Title.Text = subDirName
	linearPlot.Title.TextStyle.Font.Size = 50.0
	linearPlot.Y.Label.Text = "μs"
	linearPlot.Y.Label.TextStyle.Font.Size = 30.0
	linearPlot.X.Label.Text = "Number of elements"
	linearPlot.X.Tick.Marker = xaxis
	linearPlot.X.Label.TextStyle.Font.Size = 30.0
	linearPlot.Add(plotter.NewGrid())

	logPlot.Title.Text = subDirName + " - Log Scale"
	logPlot.Title.TextStyle.Font.Size = 50.0
	logPlot.Y.Label.Text = "log(μs + 1)"
	logPlot.Y.Scale = plot.LogScale{}
	logPlot.Y.Label.TextStyle.Font.Size = 30.0
	logPlot.X.Label.Text = "Number of elements"
	logPlot.X.Tick.Marker = xaxis
	logPlot.X.Label.TextStyle.Font.Size = 30.0
	logPlot.Add(plotter.NewGrid())

	iter := 0
	max := 0.0

	for key, yData := range data {
		if key != "elements" {
			ys, ysLog := MakePlotter(nElements, yData)

			ysLine, ysPoints, err := plotter.NewLinePoints(ys)
			if err != nil {
				log.Panic(err)
			}

			ysLine.Color = COLOURS[iter]
			ysLine.Width = vg.Length(4)
			ysPoints.Color = COLOURS[iter]
			ysPoints.Radius = vg.Points(5)
			ysPoints.Shape = draw.CircleGlyph{}

			ysLogLine, ysLogPoints, err := plotter.NewLinePoints(ysLog)
			if err != nil {
				log.Panic(err)
			}

			ysLogLine.Color = COLOURS[iter]
			ysLogLine.Width = vg.Length(4)
			ysLogPoints.Color = COLOURS[iter]
			ysLogPoints.Radius = vg.Length(5)
			ysLogPoints.Shape = draw.CircleGlyph{}

			localMax := floats.Max(yData)
			localMax = localMax + (0.1 * localMax)
			max = math.Max(max, localMax)

			linearPlot.Add(ysLine, ysPoints)
			linearPlot.Legend.Add(key, ysLine, ysPoints)

			logPlot.Add(ysLogLine, ysLogPoints)
			logPlot.Legend.Add(key, ysLogLine, ysLogPoints)

			iter += 1
		}
	}

	linearPlot.Legend.TextStyle.Font.Size = 24.0
	linearPlot.X.Tick.Label.Font.Size = 20.0
	linearPlot.Y.Tick.Label.Font.Size = 20.0
	linearPlot.Y.Max = max

	logPlot.Legend.TextStyle.Font.Size = 24.0
	logPlot.X.Tick.Label.Font.Size = 20.0
	logPlot.Y.Tick.Label.Font.Size = 20.0
	logPlot.Y.Max = max

	rootPath := RootPath()

	imgsPath := filepath.Join(rootPath, "imgs")
	if _, err := os.Stat(imgsPath); os.IsNotExist(err) {
		if err := os.Mkdir(imgsPath, os.ModePerm); err != nil {
			log.Fatal(err)
		}
	}

	subPath := filepath.Join(imgsPath, subDirName)
	if _, err := os.Stat(subPath); os.IsNotExist(err) {
		if err := os.Mkdir(subPath, os.ModePerm); err != nil {
			log.Fatal(err)
		}
	}

	savePathLinear := filepath.Join(subPath, fileName)

	if err := linearPlot.Save(1920, 1080, savePathLinear+".png"); err != nil {
		log.Panic(err)
	}

	if err := linearPlot.Save(1920, 1080, savePathLinear+".svg"); err != nil {
		log.Panic(err)
	}

	savePathLog := filepath.Join(subPath, fileName) + "Log"

	if err := logPlot.Save(1920, 1080, savePathLog+".png"); err != nil {
		log.Panic(err)
	}

	if err := logPlot.Save(1920, 1080, savePathLog+".svg"); err != nil {
		log.Panic(err)
	}
}

func PlotCSV(filePath string) {

	csvFile, err := os.Open(filePath)
	if err != nil {
		log.Fatal("Unable to read input file "+filePath, err)
	}

	csvData, err := gocsv.CSVToMaps(csvFile)
	if err != nil {
		log.Fatal(err)
	}
	defer csvFile.Close()

	data := ReconstructData(csvData)

	fileName := filepath.Base(filePath)[:len(filepath.Base(filePath))-4]
	sliceLen := len(filePath) - len(fileName) - 5
	subDir := filepath.Base(filePath[:sliceLen])
	PlotData(subDir, fileName, data)
}

func Walk(str string, dirEntry fs.DirEntry, err error) error {
	if err != nil {
		return err
	}

	if !dirEntry.IsDir() {
		if filepath.Ext(str) == ".csv" {
			PlotCSV(str)
		}
	}

	return nil
}

func Main() {

	dataPath := filepath.Join(RootPath(), "data")
	if _, err := os.Stat(dataPath); os.IsNotExist(err) {
		log.Fatal(err)
	}

	filepath.WalkDir(dataPath, Walk)
}
