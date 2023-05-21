package main

import (
	"io/fs"
	"log"
	"math"
	"os"
	"path/filepath"
	"strconv"

	"github.com/gocarina/gocsv"
	"github.com/kim89098/slice"
	"gonum.org/v1/plot"
	"gonum.org/v1/plot/plotter"
)

func root_path() string {

	ex, err := os.Executable()
	if err != nil {
		panic(err)
	}

	return filepath.Join(filepath.Dir(ex), "..")
}

func reconstruct_data(input []map[string]string) map[string][]any {
	output := make(map[string][]any)

	for _, subMap := range input {
		for key, value := range subMap {
			if _, ok := output[key]; ok {
				if key == "elements" {
					entry, _ := strconv.ParseUint(value, 10, 64)
					output[key] = append(output[key], entry)
				} else {
					entry, _ := strconv.ParseFloat(value, 64)
					output[key] = append(output[key], entry)
				}
			} else {
				if key == "elements" {
					entry, _ := strconv.ParseUint(value, 10, 64)
					output[key] = []any{entry}
				} else {
					entry, _ := strconv.ParseFloat(value, 64)
					output[key] = []any{entry}
				}
			}
		}
	}

	return output
}

func make_plotter(xValues []any, yValues []any) (plotter.XYs, plotter.XYs) {
	pts := make(plotter.XYs, len(xValues))
	ptsLog := make(plotter.XYs, len(xValues))

	for i, xy := range slice.Zip(xValues, yValues) {

		x := xy.A
		y := xy.B

		switch typedXValue := x.(type) {
		case float64:
			pts[i].X = typedXValue
			ptsLog[i].X = math.Log10(typedXValue)
		default:
			continue
		}

		switch typedYValue := y.(type) {
		case uint64:
			pts[i].Y = float64(typedYValue)
			ptsLog[i].Y = float64(typedYValue)
		default:
			continue
		}
	}

	return pts, ptsLog
}

func make_x_axis(scale []any) plot.ConstantTicks {
	ticks := make([]plot.Tick, len(scale))

	for i, value := range scale {
		switch typedValue := value.(type) {
		case uint64:
			ticks[i].Value = float64(typedValue)
			ticks[i].Label = strconv.FormatUint(typedValue, 10)
		default:
			continue
		}
	}

	return plot.ConstantTicks(ticks)
}

func plot_data(subDirName string, fileName string, data map[string][]any) {
	linearPlot := plot.New()
	logPlot := plot.New()

	nElements := data["elements"]
	xaxis := make_x_axis(nElements)

	linearPlot.Title.Text = subDirName
	linearPlot.Y.Label.Text = "μs"
	linearPlot.X.Label.Text = "Number of elements"
	linearPlot.X.Tick.Marker = xaxis

	logPlot.Title.Text = subDirName + " - Log Scale"
	logPlot.Y.Label.Text = "log(μs)"
	logPlot.Y.Scale = plot.LogScale{}
	logPlot.X.Label.Text = "Number of elements"
	logPlot.X.Tick.Marker = xaxis

	for key, xData := range data {
		if key != "elements" {
			xs, _ := make_plotter(xData, nElements)

			xsLine, xsPoints, err := plotter.NewLinePoints(xs)
			if err != nil {
				log.Panic(err)
			}

			// xsLogLine, xsLogPoints, err := plotter.NewLinePoints(xsLog)
			// if err != nil {
			// 	log.Panic(err)
			// }

			linearPlot.Add(xsLine, xsPoints)
			linearPlot.Legend.Add(key)

			// logPlot.Add(xsLogLine, xsLogPoints)
			// logPlot.Legend.Add(key)
		}
	}

	rootPath := root_path()

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

	savePathLinear := filepath.Join(subPath, fileName) + ".png"
	if err := linearPlot.Save(1000, 1000, savePathLinear); err != nil {
		log.Panic(err)
	}

	// savePathLog := filepath.Join(subPath, fileName) + "Log.png"
	// if err := logPlot.Save(100, 100, savePathLog); err != nil {
	// 	log.Panic(err)
	// }
}

func plot_csv(filePath string) {

	csvFile, err := os.Open(filePath)
	if err != nil {
		log.Fatal("Unable to read input file "+filePath, err)
	}

	csvData, err := gocsv.CSVToMaps(csvFile)
	if err != nil {
		log.Fatal(err)
	}
	defer csvFile.Close()

	data := reconstruct_data(csvData)

	fileName := filepath.Base(filePath)[:len(filepath.Base(filePath))-4]
	sliceLen := len(filePath) - len(fileName) - 5
	subDir := filepath.Base(filePath[:sliceLen])
	plot_data(subDir, fileName, data)
}

func walk(str string, dirEntry fs.DirEntry, err error) error {
	if err != nil {
		return err
	}

	if !dirEntry.IsDir() {
		if filepath.Ext(str) == ".csv" {
			plot_csv(str)
		}
	}

	return nil
}

func main() {

	dataPath := filepath.Join(root_path(), "data")
	if _, err := os.Stat(dataPath); os.IsNotExist(err) {
		log.Fatal(err)
	}

	filepath.WalkDir(dataPath, walk)

	// csvFile, err := os.Open(filePath)
	// if err != nil {
	// 	log.Fatal("Unable to read input file "+filePath, err)
	// }
	// doc := csv.NewReader(csvFile)
	// defer csvFile.Close()
	// doc.Read()
}
