node { 
    stage('Checkout project') {
        checkout scm
    }

    stage('Install and build dependencies') {
        dir('build') {
            sh 'conan install .. --build=missing'
        }
    }

    stage('Build with conan') {
        dir('build') {
            sh 'conan build ..'
        }
    }

    stage('Doxygen') {
        tool name: 'doxygen', type: 'hudson.plugins.doxygen.DoxygenInstallation'
    }

    stage('Archive artifacts') {
        archiveArtifacts artifacts: 'bin/inexor,bin/inexor.exe,bin/RPCTreeData-inexor.proto', fingerprint: true, onlyIfSuccessful: true
    }

}
