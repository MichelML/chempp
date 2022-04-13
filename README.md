**In Development** 

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![Apache License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

<br />
<p align="center">
  <a href="https://github.com/michelml/chempp">
    <img src="chempp.png" alt="Chempp - Project Logo" width="200" height="200">
  </a>

  <p align="center">
    [Large scale] concurrent chemical search engine using RDKit cartridge, Oat++ and native Postgres & C++ features.
    <br />
    <a href="https://github.com/michelml/chempp"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/michelml/chempp">View Demo</a>
    ·
    <a href="https://github.com/michelml/chempp/issues">Report Bug</a>
    ·
    <a href="https://github.com/michelml/chempp/issues">Request Feature</a>
  </p>
</p>



<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary><h2 style="display: inline-block">Table of Contents</h2></summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Installation</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#install-steps">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgements">Acknowledgements</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

**chempp** [kem-pee-pee], is a large scale concurrent chemical search engine using RDKit cartridge, Oat++ and native Postgres & C++ features.

### Built With

* [Oat++](https://oatpp.io/)
* [PostgreSQL RDKit cartridge](https://rdkit.org/docs/Cartridge.html)
* [PostgreSQL](https://www.postgresql.org/)
* Special mention to Arthur Farias for his very well crafted [url encoding/decoding C++ gist](https://gist.github.com/arthurafarias/56fec2cd49a32f374c02d1df2b6c350f)

## Installation

### Prerequisites

- Knowledge of what a [SMILES](https://en.wikipedia.org/wiki/Simplified_molecular-input_line-entry_system) is in chemistry
- Knowledge of what a [SMARTS](https://en.wikipedia.org/wiki/SMILES_arbitrary_target_specification) is in chemistry
- [Git](https://git-scm.com/)
- [Docker and Docker-Compose](https://www.docker.com/)

### Install steps

Clone the project

```bash
git clone https://github.com/MichelML/chempp.git && \
cd chempp
```

Then, start the db and fill it with molecules. You have two options:

#### Option 1 - Small Database of 1000 molecules

```bash
docker-compose up -d db && \
docker-compose exec db bash -c "SMALLDB=1 /utility/populate_db.sh"
```

#### Option 2 - Large database of ~3M compounds

```bash
docker-compose up -d db && \
docker-compose exec db bash -c "/utility/populate_db.sh"
```

> **Warning:** This command will take a while because it inserts ~3M rows in the db and [creates indexes to perform efficient searches](https://rdkit.org/docs/Cartridge.html), a rough estimate being between 15 minutes and an hour.

Lastly, start the chempp service:

```bash
docker-compose up service
```

Once these commands are ran, you are ready to test the endpoints at http://localhost:8000/swagger/ui .

<!-- USAGE EXAMPLES -->
## Usage

See usage through Swagger demo here https://drive.google.com/file/d/1FKh3-N4KWvVEz7NPFmMDALWu-BzYbaHP/view?usp=sharing .

<!-- ROADMAP -->
## Roadmap

See the [open issues](https://github.com/michelml/chempp/issues) for a list of proposed features (and known issues).

<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

Make sure to format your code properly with `make format`.

<!-- LICENSE -->
## License

Distributed under the Apache-2.0 License. See `LICENSE` for more information.



<!-- CONTACT -->
## Contact

Michel ML - [@michelml](https://github.com/MichelML) - michmoreau.l@gmail.com

Project Link: [https://github.com/michelml/chempp](https://github.com/michelml/chempp)

<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements

Thank you to all contributors of libraries and tools used in this project.

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/michelml/chempp.svg?style=for-the-badge
[contributors-url]: https://github.com/michelml/chempp/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/michelml/chempp.svg?style=for-the-badge
[forks-url]: https://github.com/michelml/chempp/network/members
[stars-shield]: https://img.shields.io/github/stars/michelml/chempp.svg?style=for-the-badge
[stars-url]: https://github.com/michelml/chempp/stargazers
[issues-shield]: https://img.shields.io/github/issues/michelml/chempp.svg?style=for-the-badge
[issues-url]: https://github.com/michelml/chempp/issues
[license-shield]: https://img.shields.io/github/license/michelml/chempp.svg?style=for-the-badge
[license-url]: https://github.com/michelml/chempp/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/michelmoreau1/
[product-screenshot]: chempp.png
