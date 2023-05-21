package main

import (
	"io/fs"
	"log"
	"os"
	"path/filepath"
	"strconv"

	"github.com/gocarina/gocsv"
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

func plot_data(subDirName string, fileName string, data map[string][]any) {
	p := plot.New()

	quad := plotter.NewFunction(func(x float64) float64 { return x * x })
	p.Add(quad)

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
	if err := p.Save(100, 100, savePathLinear); err != nil {
		log.Panic(err)
	}

	savePathLog := filepath.Join(subPath, fileName) + "Log.png"
	if err := p.Save(100, 100, savePathLog); err != nil {
		log.Panic(err)
	}
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
