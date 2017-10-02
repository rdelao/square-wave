import sbt.Keys.{ivyXML, scalaVersion}

name := "noise-analyzer"

shellPrompt in ThisBuild := { state => s"${Project.extract(state).currentRef.project}-${version.value}> " }

lazy val commonSettings = Seq(
  organization := "rdelao",

  scalaVersion := "2.11.8",

  scalacOptions ++= Seq("-deprecation", "-unchecked", "-feature", "-Xlint", "-language:postfixOps",
    "-language:implicitConversions", "-language:higherKinds"),

  fork := true,

  mainClass in(Compile, run) := Some("rdelao.Analyzer"),

  resolvers ++= Seq(
    "Sonatype OSS Snapshots" at "https://oss.sonatype.org/content/repositories/snapshots",
    "Typesafe Releases" at "https://repo.typesafe.com/typesafe/maven-releases/",
    "Maven central" at "https://repo1.maven.org/maven2/",
    "Sonatype Releases" at "https://oss.sonatype.org/content/repositories/releases/",
    "scalac repo" at "https://raw.githubusercontent.com/ScalaConsultants/mvn-repo/master/"
  ),

  libraryDependencies ++= Seq(
    "com.typesafe" % "config" % "1.3.1",
    "org.scalanlp" %% "breeze" % "0.12",
    "org.scalanlp" %% "breeze-natives" % "0.12",
    "org.scalanlp" %% "breeze-viz" % "0.12"
  )
)

lazy val root = Project(
  id = "root",
  base = file(".")
).settings(commonSettings)
.aggregate(analyzer)

lazy val analyzer = Project(
  id = "noise-analyzer",
  base = file("noise-analyzer")
).settings(commonSettings)

